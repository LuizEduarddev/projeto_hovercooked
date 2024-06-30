#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "pronto.h" 
#include "preparo.h"
#include "pedidos.h"
#include "tela.h"
#include "lista_encadeada_struct.h"
#include "jogo.h"

pthread_mutex_t tela_mutex = PTHREAD_MUTEX_INITIALIZER;
volatile int jogo_ativo = 1;  // Variável global para controlar o estado do jogo
int ganhou = 0;

void start()
{
    pthread_t thread_gera_pedido;
    struct gancho *cabeca_pedidos = criar_lista_No();
    struct gancho *cabeca_pronto = criar_lista_No();
    struct gancho *cabeca_preparo = criar_lista_No();
    pthread_create(&thread_gera_pedido, NULL, gera_pedidos, (void *)cabeca_pedidos);
    gera_tela(cabeca_pedidos, cabeca_preparo, cabeca_pronto);
}

struct tela_struct *create_variable_tela(struct gancho *cabeca_pedidos, struct gancho *cabeca_preparo, struct gancho *cabeca_pronto)
{
    struct tela_struct *tela_data;

    tela_data = (struct tela_struct *)malloc(sizeof(struct tela_struct));
    if (tela_data == NULL) {
        fprintf(stderr, "Failed to allocate memory for tela_data\n");
        exit(EXIT_FAILURE);
    }

    tela_data->cabeca_pedido = cabeca_pedidos;
    tela_data->cabeca_preparo = cabeca_preparo;
    tela_data->cabeca_pronto = cabeca_pronto;
    tela_data->bancadas_maximas = 2;
    return tela_data;
}

void gera_tela(struct gancho *cabeca_pedidos, struct gancho *cabeca_preparo, struct gancho *cabeca_pronto)
{
    pthread_t thread_tela;
    struct tela_struct *tela_data = create_variable_tela(cabeca_pedidos, cabeca_preparo, cabeca_pronto);
    pthread_create(&thread_tela, NULL, thread_func_tela, (void* )tela_data);
    pthread_join(thread_tela, NULL);
}

void encerra_jogo()
{
    jogo_ativo = 0;  // Define a variável global para indicar que o jogo deve ser encerrado
}

void gera_tela_comandos(struct tela_struct *tela_data)
{
    pthread_t thread_comandos;
    pthread_create(&thread_comandos, NULL, pega_comandos, (void *)tela_data);
}

void *pega_comandos(void * tel)
{
    struct tela_struct *tela_data = (struct tela_struct *)tel;
    int tecla;
    do {
        tecla = getch();
        switch (tecla) {
            case '1':
                preparar_item(tela_data->cabeca_pedido, tela_data->cabeca_preparo, tela_data);
                break;
            case '2':
                preparar_item(tela_data->cabeca_preparo, tela_data->cabeca_pronto, tela_data);
                break;
            case KEY_F(4):
            case 'q':
                encerra_jogo();
                break;
            default:
                break;
        }
    } while (jogo_ativo);
    return NULL;
}

void *thread_func_tela(void* tel)
{
    struct tela_struct *tela_data = (struct tela_struct *)tel;
    initscr();
    start_color();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);

    pthread_mutex_lock(&tela_mutex);
    move(0, 0);
    printw("Iniciando...");
    refresh();
    sleep(1);

    move(0, 0);
    printw("1 - Preparar ingredientes | 2 - Preparar Pedido | F4 ou Q para encerrar o programa.");
    pthread_mutex_unlock(&tela_mutex);

    gera_tela_comandos(tela_data);
    while (jogo_ativo) {
        pthread_mutex_lock(&tela_mutex);
        clear();
        move(0, 0);
        printw("1 - Preparar ingredientes | 2 - Preparar Pedido | F4 ou Q para encerrar o programa.");
        move(1,0);
        printw("'%d' bancadas em uso", tela_data->bancadas_atuais);
        move(2,0);
        printw("'%d' cozinheiros trabalhando", tela_data->cozinheiros_atuais);
        printa_tela_pedidos(tela_data->cabeca_pedido);
        ver_preparo_func__(tela_data->cabeca_preparo);
        ver_pronto_func__(tela_data->cabeca_pronto);
        pthread_mutex_unlock(&tela_mutex);
        sleep(1);
    }

    pthread_mutex_lock(&tela_mutex);
    keypad(stdscr, FALSE);
    noraw();
    echo();
    endwin();
    pthread_mutex_unlock(&tela_mutex);

    printw("Termino da execucao\n");

    return NULL;
}
