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

void start()
{
    pthread_t thread_gera_pedido;
    struct gancho_pedidos *cabeca_pedidos = criar_lista_pedidos();
    struct gancho_pronto *cabeca_pronto = criar_lista_pronto();
    struct gancho_preparo *cabeca_preparo = criar_lista_preparo();
    pthread_create(&thread_gera_pedido, NULL, gera_pedidos, (void *)cabeca_pedidos);
    gera_tela(cabeca_pedidos, cabeca_preparo, cabeca_pronto);
}

struct tela_struct *create_variable_tela(struct gancho_pedidos *cabeca_pedidos, struct gancho_preparo *cabeca_preparo, struct gancho_pronto *cabeca_pronto)
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
    return tela_data;
}

void gera_tela(struct gancho_pedidos *cabeca_pedidos, struct gancho_preparo *cabeca_preparo, struct gancho_pronto *cabeca_pronto)
{
    pthread_t thread_tela;
    struct tela_struct *tela_data = create_variable_tela(cabeca_pedidos, cabeca_preparo, cabeca_pronto);
    pthread_create(&thread_tela, NULL, thread_func_tela, (void* )tela_data);
}

void *thread_func_tela(void* tel)
{
    struct tela_struct *tela_data = (struct tela_struct *)tel;
    int tecla;
    initscr(); // Inicializa a tela (posição atual é (0, 0))
    start_color();
    raw();    // Não precisa esperar uma quebra de linha
    noecho(); // O que for digitado não aparece na tela
    keypad(stdscr, TRUE); // Teclas especiais como F1, F2, etc..

    // Cria as cores que serão utilizadas (mas ainda não usa)
    init_pair(7, COLOR_BLACK, COLOR_WHITE); // padrão
    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);

    printw("Iniciando...");
    refresh(); // Realiza todos os comandos pendentes atualizando na tela
    sleep(1);

    attron(COLOR_PAIR(5));
    mvprintw(LINES - 1, 0, "(%d - %d) - Pressione 'q' para sair...", LINES, COLS);
    attroff(COLOR_PAIR(5));

    move(0, 0);
    printw(" - Digite 1, 2, q ou F4: ");
    do {
        tecla = getch();
        switch (tecla) {
            case '1':
                ver_pedidos(tela_data->cabeca_pedido);
                break;
            /*
            case '2':
                printw("Apertou 2");
                break;
            */
            case KEY_F(4):
                attron(COLOR_PAIR(7));
                move(8, 0);
                printw("Tecla F4 foi pressionada.. saindo");
                refresh();
                sleep(1);
            case 'q':
            default:
                break;
        }
    } while (tecla != 'q' && tecla != KEY_F(4));

    // Desabilitando tudo que foi habilitado antes de sair, para não deixar o
    // terminal em estado diferente do anterior à execução
    keypad(stdscr, FALSE);
    noraw();
    echo();

    endwin();

    printf("Termino da execucao\n");

    return 0;
}
