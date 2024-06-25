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
    struct gancho_pedidos *cabeca_pedidos = criar_lista_pedidos();
    struct gancho_pronto *cabeca_pronto = criar_lista_pronto();
    struct gancho_preparo *cabeca_preparo = criar_lista_preparo();
    gera_pedido(cabeca_pedidos);
    gera_tela(cabeca_pedidos, cabeca_preparo, cabeca_pronto);
}

void gera_tela(struct gancho_pedidos *cabeca_pedidos, struct gancho_preparo *cabeca_preparo, struct gancho_pronto *cabeca_pronto)
{
    pthread_t thread_tela;
    struct tela_struct *tela_data;
    tela_data->cabeca_pedido = cabeca_pedidos;
    tela_data->cabeca_preparo = cabeca_preparo;
    tela_data->cabeca_pronto = cabeca_pronto;
    pthread_create(&thread_tela, NULL, thread_func_tela, (void* )tela_data);
}

void *thread_func_tela(void* tel)
{
    int tecla;
    struct tela_struct *tela_data = tel;
    initscr();
    start_color();
    raw(); 
    noecho();
    keypad(stdscr, TRUE);

    init_pair(7, COLOR_BLACK, COLOR_WHITE); 
    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);

    printw("Iniciando...");
    refresh(); 
    sleep(1);   

    attron(COLOR_PAIR(5));
    mvprintw(LINES - 1, 0, "(%d - %d) - Pressione 'q' para sair...", LINES, COLS);
    attroff(COLOR_PAIR(5));

    move(0, 0);
    printw(" - Digite\n1 - Ver pedidos\nF4 - Sair do programa: ");
    while (tecla != 'q' && tecla != KEY_F(4))
    {
        tecla = getch();
        switch (tecla)
        {
        case '1':
            ver_pedidos(tela_data->cabeca_pedido);
            break;
        /*
        case '2':
            selecionar_bancada();
            break;
        */
        default:
            break;
        }
    }

    keypad(stdscr, FALSE);
    noraw();
    echo();

    endwin();

    printf("Termino da execucao\n");

    return 0;
}