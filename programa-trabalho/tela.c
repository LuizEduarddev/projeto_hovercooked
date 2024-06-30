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

void *thread_tela_infinita(void* tel)
{
    struct tela_struct *tela_data = (struct tela_struct *) tel;
    pthread_t thread_preparo;
    pthread_t thread_pronto;
    while(1)
    {
        pthread_create(&thread_preparo, NULL, thread_ver_preparo_func, (void *)tela_data->cabeca_preparo);
        pthread_join(thread_preparo, NULL);
        pthread_create(&thread_pronto, NULL, thread_ver_pronto_func, (void *)tela_data->cabeca_preparo);
        pthread_join(thread_pronto, NULL);
    }
}

void inicia_thread_mostra_tela(struct tela_struct *tela_data)
{
    pthread_t gera_tela;
    pthread_create(&gera_tela, NULL, thread_tela_infinita, (void *)tela_data);
}

void *thread_func_tela(void* tel)
{
    struct tela_struct *tela_data = (struct tela_struct *)tel;
    inicia_thread_mostra_tela(tela_data);
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

    move(0,30);
    printw("Iniciando...");
    refresh(); // Realiza todos os comandos pendentes atualizando na tela
    sleep(1);

    do {
        move(0, 30);
        printw(" - Digite 1 - Preparar Item | 2, q ou F4: \n");
        tecla = getch();
        switch (tecla) {
            case '1':
                preparar_item(tela_data);
                break;
            case '2':
                item_pronto(tela_data);
                break;
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

    printw("Termino da execucao\n");

    return 0;
}
