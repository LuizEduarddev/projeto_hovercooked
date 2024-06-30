#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include "pronto.h" 
#include "preparo.h"
#include "pedidos.h"
#include "tela.h"
#include "lista_encadeada_struct.h"
#include "jogo.h"

void ativar_bancada(struct No *pedidos, struct tela_struct *tela)
{
    tela->cozinheiros_atuais += 1;
    tela->bancadas_atuais += 1;
    deletar_item_pedido(pedidos, tela->cabeca_pedido);
    sleep(pedidos->tempo_fazer);
    adicionar_item(tela->cabeca_preparo, pedidos->prato, pedidos->tempo_fazer, "preparo");
    tela->cozinheiros_atuais -= 1;
    tela->bancadas_atuais -= 1;
    return;
}

void *thread_bancada_func(void *varrer)
{
    int cont = 0;
    struct struct_varrimento *varrimento = (struct struct_varrimento *) varrer;
    struct No *pedidos = varrimento->tela->cabeca_pedido->primeiro;
    while (pedidos != NULL)
    {
        if (pedidos->numero_pedido == varrimento->tecla)
        {
            cont = 1;
            ativar_bancada(pedidos, varrimento->tela);
        }
        pedidos = pedidos->proximo;
    }
    /*
    if (cont == 0)
    {
        move(3,0);
        printw("Id de pedido nao encontrado.\n");
    }
    */
}

void seta_cozinheiro_item(struct tela_struct *tela_data, int tecla)
{
    /*
    if (tela_data->cozinheiros_atuais == tela_data->bancadas_maximas)
    {
        move(2,0);
        clrtoeol();
        printw("Todos os '%d' cozinheiros estao ocupados. Bancadas restantes '0'.", tela_data->cozinheiros_atuais);
        sleep(2);
        return;
    }
    else{
    }
    */
    pthread_t thread_bancada;
    struct struct_varrimento *varrimento;
    varrimento = (struct struct_varrimento *)malloc(sizeof(struct struct_varrimento));
    if (varrimento != NULL)
    {
        varrimento->tela = tela_data;
        varrimento->tecla = tecla;
        pthread_create(&thread_bancada, NULL, thread_bancada_func, (void *)varrimento);
    }
    /*
    else{
        move(3,0);
        printw("Ocorreu um erro durante a instanciacao de 'varrimento'.\n");
        return;
    }
    */
}

void preparar_item(struct tela_struct *tela_data)
{   
    int tecla;

    pthread_mutex_lock(&tela_mutex);
    move(0, 0);
    clrtoeol();
    printw("----- Selecione um id de pedido para adicionar a bancada. ------");
    tecla = getch();
    tecla = tecla - '0';
    if (tecla >= 1 && tecla <= 9)
    {
        seta_cozinheiro_item(tela_data, tecla);
    }
    else {
        move(2, 0);
        clrtoeol(); 
        printw("tecla invalida");
    }
    pthread_mutex_unlock(&tela_mutex);
    clear();
}

void *thread_bancada_pronto_func(void *varrer)
{
    int cont = 0;
    struct struct_varrimento *varrimento = (struct struct_varrimento *) varrer;
    struct No *pedidos = varrimento->tela->cabeca_pronto->primeiro;
    while (pedidos != NULL)
    {
        if (pedidos->numero_pedido == varrimento->tecla)
        {
            cont = 1;
            ativar_bancada(pedidos, varrimento->tela);
        }
        pedidos = pedidos->proximo;
    }
    if (cont == 0)
    {
        move(3,0);
        printw("Id de pedido nao encontrado.\n");
    }
    clear();
}

void seta_cozinheiro_pronto(struct tela_struct *tela_data, int tecla)
{
    /*
    if (tela_data->cozinheiros_atuais == tela_data->bancadas_maximas)
    {
        move(2,0);
        clrtoeol();
        printw("Todos os '%d' cozinheiros estao ocupados. Bancadas restantes '0'.", tela_data->cozinheiros_atuais);
        sleep(2);
        clear();
        return;
    }
    
    else{
    }
    */
    pthread_t thread_bancada_pronto;
    struct struct_varrimento *varrimento;
    varrimento = (struct struct_varrimento *)malloc(sizeof(struct struct_varrimento));
    if (varrimento != NULL)
    {
        varrimento->tela = tela_data;
        varrimento->tecla = tecla;
        pthread_create(&thread_bancada_pronto, NULL, thread_bancada_pronto_func, (void *)varrimento);
    }
        /*
        else{
            move(3,0);
            printw("Ocorreu um erro durante a instanciacao de 'varrimento'.\n");
            clear();
            return;
        }
        */
}

void item_pronto(struct tela_struct *tela_data)
{
    int tecla;

    pthread_mutex_lock(&tela_mutex);
    move(0, 0);
    clrtoeol();
    printw("----- Selecione um id de pedido para adicionar a bancada. ------");
    tecla = getch();
    tecla = tecla - '0';
    if (tecla >= 1 && tecla <= 9)
    {
        seta_cozinheiro_pronto(tela_data, tecla);
    }
    else {
        move(2, 0);
        clrtoeol(); 
        printw("tecla invalida");
    }
    pthread_mutex_unlock(&tela_mutex);
    clear();
}

