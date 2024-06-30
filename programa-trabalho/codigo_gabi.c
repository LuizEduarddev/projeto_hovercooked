#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <ncurses.h>
#include <string.h>

#define MAX_PEDIDOS 15
#define MAX_COZINHEIROS 4
#define MAX_BANCADAS 3
#define MAX_COZINHAS 4

#define TEMPO_PIZZA 5
#define TEMPO_HAMBURGUER 3
#define TEMPO_SUCO 2

typedef struct {
    int codigo;
    int tempo_preparo_ingredientes;
    int tempo_preparo_prato;
    char nome[20];
} Prato;

typedef struct {
    int id;
    int estado;
    int prato;
    int tempoRestante;
    int bancada;
    int cozinha;
    pthread_cond_t cond_inicio_preparo;
    pthread_t thread;
} Cozinheiro;

Prato pratos[] = {
    {11, TEMPO_PIZZA, TEMPO_PIZZA, "Pizza"},
    {12, TEMPO_HAMBURGUER, TEMPO_HAMBURGUER, "Hamburguer"},
    {13, TEMPO_SUCO, TEMPO_SUCO, "Suco"}
};
Cozinheiro cozinheiros[MAX_COZINHEIROS];
int bancadas[MAX_BANCADAS] = {0};
int cozinhas[MAX_COZINHAS] = {0};
int pedidos[MAX_PEDIDOS];
int numPedidos;
int tempoJogo;
int tempoTotal = 0;
int pedidoAtual = 0;
int pedidosConcluidos = 0;

sem_t semaforo_bancada, semaforo_cozinha;
pthread_mutex_t mutex_tela, mutex_pedidos;

WINDOW *tela_pedidos, *tela_cozinheiros, *tela_recursos;
pthread_t gerente_thread, mural_pedidos_thread;

void inicializar_ncurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    tela_pedidos = newwin(17, 20, 0, 0);
    tela_cozinheiros = newwin(11, 40, 0, 20);
    tela_recursos = newwin(11, 50, 0, 60);

    box(tela_pedidos, 0, 0);
    box(tela_cozinheiros, 0, 0);
    box(tela_recursos, 0, 0);

    mvwprintw(tela_pedidos, 0, 1, " Pedidos ");
    mvwprintw(tela_cozinheiros, 0, 1, " Cozinheiros ");
    mvwprintw(tela_recursos, 0, 1, " Recursos ");

    refresh();
    wrefresh(tela_pedidos);
    wrefresh(tela_cozinheiros);
    wrefresh(tela_recursos);
}

void atualizar_tela() {
    wclear(tela_pedidos);
    wclear(tela_cozinheiros);
    wclear(tela_recursos);

    box(tela_pedidos, 0, 0);
    box(tela_cozinheiros, 0, 0);
    box(tela_recursos, 0, 0);

    mvwprintw(tela_pedidos, 1, 1, "Pedidos:");
    for (int i = 0; i < numPedidos; i++) {
        if (i < pedidosConcluidos) {
            mvwprintw(tela_pedidos, i + 2, 1, "%d (Concluído)", pedidos[i]);
        } else {
            mvwprintw(tela_pedidos, i + 2, 1, "%d", pedidos[i]);
        }
    }

    mvwprintw(tela_cozinheiros, 1, 1, "Cozinheiros:");
    for (int i = 0; i < MAX_COZINHEIROS; i++) {
        mvwprintw(tela_cozinheiros, i + 2, 1, "Cozinheiro %d: ", i + 1);
        switch (cozinheiros[i].estado) {
            case 0:
                mvwprintw(tela_cozinheiros, i + 2, 14, "Disponivel");
                break;
            case 1:
                mvwprintw(tela_cozinheiros, i + 2, 14, "Prep. Ingredientes");
                mvwprintw(tela_cozinheiros, i + 2, 35, "(%d)", cozinheiros[i].tempoRestante);
                break;
            case 2:
                mvwprintw(tela_cozinheiros, i + 2, 14, "Prep. Prato");
                mvwprintw(tela_cozinheiros, i + 2, 25, "(%d)", cozinheiros[i].tempoRestante);
                break;
        }
    }

    mvwprintw(tela_recursos, 1, 1, "Bancadas:");
    for (int i = 0; i < MAX_BANCADAS; i++) {
        mvwprintw(tela_recursos, i + 2, 1, "Bancada %d: %s", i + 1, bancadas[i] == 0 ? "Livre" : "Ocupada");
    }

    mvwprintw(tela_recursos, MAX_BANCADAS + 2, 1, "Cozinhas:");
    for (int i = 0; i < MAX_COZINHAS; i++) {
        mvwprintw(tela_recursos, MAX_BANCADAS + i + 3, 1, "Cozinha %d: %s", i + 1, cozinhas[i] == 0 ? "Livre" : "Ocupada");
    }

    mvwprintw(stdscr, 12, 21, "Comandos:");  // Movido para a direita, a partir da coluna 21
    for (int i = 0; i < MAX_COZINHEIROS; i++) {
        mvwprintw(stdscr, 13 + i, 21, "Cozinheiro %d: 11 (Pizza), 12 (Hamburguer), 13 (Suco)", i + 1);
    }

    refresh();
    wrefresh(tela_pedidos);
    wrefresh(tela_cozinheiros);
    wrefresh(tela_recursos);
}

void *cozinheiro(void *arg) {
    Cozinheiro *c = (Cozinheiro *)arg;

    while (1) {
        pthread_mutex_lock(&mutex_pedidos);
        pthread_cond_wait(&c->cond_inicio_preparo, &mutex_pedidos);

        if (pedidoAtual >= numPedidos) {
            pthread_mutex_unlock(&mutex_pedidos);
            break;
        }

        Prato *prato_info = &pratos[c->prato - 11];
        pthread_mutex_unlock(&mutex_pedidos);

        sem_wait(&semaforo_bancada);
        c->estado = 1;
        for (int i = 0; i < MAX_BANCADAS; i++) {
            if (bancadas[i] == 0) {
                pthread_mutex_lock(&mutex_tela);
                bancadas[i] = c->id;
                c->bancada = i + 1;
                atualizar_tela();
                pthread_mutex_unlock(&mutex_tela);
                break;
            }
        }
        c->tempoRestante = prato_info->tempo_preparo_ingredientes;
        sleep(1);

        while (c->tempoRestante > 0) {
            sleep(1);
            c->tempoRestante--;
            pthread_mutex_lock(&mutex_tela);
            atualizar_tela();
            pthread_mutex_unlock(&mutex_tela);
        }

        sem_post(&semaforo_bancada);
        bancadas[c->bancada - 1] = 0;

        sem_wait(&semaforo_cozinha);
        c->estado = 2;
        for (int i = 0; i < MAX_COZINHAS; i++) {
            if (cozinhas[i] == 0) {
                cozinhas[i] = c->id;
                c->cozinha = i + 1;
                pthread_mutex_lock(&mutex_tela);
                atualizar_tela();
                pthread_mutex_unlock(&mutex_tela);
                break;
            }
        }
        c->tempoRestante = prato_info->tempo_preparo_prato;

        while (c->tempoRestante > 0) {
            sleep(1);
            c->tempoRestante--;
            pthread_mutex_lock(&mutex_tela);
            atualizar_tela();
            pthread_mutex_unlock(&mutex_tela);
        }

        sem_post(&semaforo_cozinha);
        cozinhas[c->cozinha - 1] = 0;

        c->estado = 0;
        c->prato = 0;

        pthread_mutex_lock(&mutex_tela);
        atualizar_tela();
        mvwprintw(stdscr, 7, 0, "Cozinheiro %d preparou %s!", c->id, prato_info->nome);
        refresh();
        pthread_mutex_unlock(&mutex_tela);
        sleep(1);

        pthread_mutex_lock(&mutex_pedidos);
        pedidosConcluidos++;
        pthread_mutex_unlock(&mutex_pedidos);
    }

    pthread_exit(NULL);
}

void *gerente(void *arg) {
    int tecla1, tecla2;

    while (tempoTotal < tempoJogo || tempoJogo == -1) {
        tecla1 = getch();
        tecla2 = getch();

        int cozinheiro = tecla1 - '0';
        int prato = (tecla2 - '0') + 10;

        if (cozinheiro >= 1 && cozinheiro <= MAX_COZINHEIROS && prato >= 11 && prato <= 13) {
            pthread_mutex_lock(&mutex_pedidos);
            if (cozinheiros[cozinheiro - 1].estado == 0) {
                cozinheiros[cozinheiro - 1].prato = prato;
                pthread_cond_signal(&cozinheiros[cozinheiro - 1].cond_inicio_preparo);
            } else {
                pthread_mutex_lock(&mutex_tela);
                mvwprintw(stdscr, 7, 0, "Cozinheiro %d ou recursos indisponíveis!", cozinheiro);
                refresh();
                pthread_mutex_unlock(&mutex_tela);
                sleep(1);
            }
            pthread_mutex_unlock(&mutex_pedidos);
        } else {
            pthread_mutex_lock(&mutex_tela);
            mvwprintw(stdscr, 7, 0, "Comando inválido!");
            refresh();
            pthread_mutex_unlock(&mutex_tela);
            sleep(1);
        }

        pthread_mutex_lock(&mutex_tela);
        atualizar_tela();
        pthread_mutex_unlock(&mutex_tela);
    }

    pthread_exit(NULL);
}

void *mural_pedidos(void *arg) {
    while (pedidosConcluidos < numPedidos) {
        int prato = (rand() % 3) + 11;

        pthread_mutex_lock(&mutex_pedidos);
        if (pedidoAtual < numPedidos) {
            pedidos[pedidoAtual++] = prato;
        }
        pthread_mutex_unlock(&mutex_pedidos);

        pthread_mutex_lock(&mutex_tela);
        atualizar_tela();
        pthread_mutex_unlock(&mutex_tela);

        sleep(rand() % 5 + 1);
    }

    pthread_exit(NULL);
}

void fim_de_jogo() {
    clear();
    mvprintw(LINES / 2, (COLS - strlen("Fim de Jogo! Obrigado por jogar.")) / 2, "Fim de Jogo! Obrigado por jogar.");
    mvprintw(LINES / 2 + 1, (COLS - strlen("Pressione qualquer tecla (nao numerica) para sair.")) / 2, "Pressione qualquer tecla (nao numerica) para sair.");
    refresh();
    getch();
    endwin();

    pthread_mutex_destroy(&mutex_tela);
    pthread_mutex_destroy(&mutex_pedidos);
    sem_destroy(&semaforo_bancada);
    sem_destroy(&semaforo_cozinha);

    exit(0);
}

int main() {
    srand(time(NULL));

    int nivel;
    printf("Escolha o nível de dificuldade (1: Fácil, 2: Médio, 3: Difícil): ");
    scanf("%d", &nivel);

    switch (nivel) {
        case 1:
            tempoJogo = -1;
            break;
        case 2:
        case 3:
            printf("Digite o tempo de jogo (segundos): ");
            scanf("%d", &tempoJogo);
            break;
        default:
            printf("Nível inválido. Usando nível fácil.\n");
            tempoJogo = -1;
    }

    int numCozinheiros = (nivel == 3) ? 4 : MAX_COZINHEIROS;
    int numBancadas = (nivel == 3) ? 2 : MAX_BANCADAS;
    int numCozinhas = numCozinheiros;

    switch (nivel) {
        case 1:
            numPedidos = (rand() % 5) + 1;
            break;
        case 2:
            numPedidos = (rand() % 5) + 6;
            break;
        case 3:
            numPedidos = (rand() % 5) + 11;
            break;
    }

    inicializar_ncurses();

    pthread_mutex_init(&mutex_tela, NULL);
    pthread_mutex_init(&mutex_pedidos, NULL);
    sem_init(&semaforo_bancada, 0, numBancadas);
    sem_init(&semaforo_cozinha, 0, numCozinhas);

    for (int i = 0; i < numCozinheiros; i++) {
        cozinheiros[i].id = i + 1;
        cozinheiros[i].estado = 0;
        pthread_cond_init(&cozinheiros[i].cond_inicio_preparo, NULL);
        pthread_create(&cozinheiros[i].thread, NULL, cozinheiro, (void *)&cozinheiros[i]);
    }

    pthread_create(&gerente_thread, NULL, gerente, NULL);
    pthread_create(&mural_pedidos_thread, NULL, mural_pedidos, NULL);

    while ((tempoTotal < tempoJogo || tempoJogo == -1) && pedidosConcluidos < numPedidos) {
        tempoTotal++;
        sleep(1);

        pthread_mutex_lock(&mutex_tela);
        atualizar_tela();
        pthread_mutex_unlock(&mutex_tela);

        if (tempoTotal >= tempoJogo && tempoJogo != -1) {
            fim_de_jogo();
        }
    }

    fim_de_jogo();
    
    return 0;
}