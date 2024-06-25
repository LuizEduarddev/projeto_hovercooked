#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "pedidos.h"

struct gancho_pedidos* criar_lista_pedidos(void)
{
    struct gancho_pedidos *cabeca = (struct gancho_pedidos *)(malloc(sizeof(struct gancho_pedidos)));
    cabeca->primeiro = NULL;
    return cabeca;
}

void adicionar_item_pedido(struct gancho_pedidos *cabeca, char *prato, int tempo_fazer)
{
    struct pedidos* novo = (struct pedidos *)(malloc(sizeof(struct pedidos)));
    novo->tempo_fazer = tempo_fazer;
    strcpy(novo->prato, prato);
    if (cabeca->primeiro == NULL)
    {
        cabeca->primeiro = novo;
        novo->anterior = NULL;
        novo->proximo = NULL;
    }
    else{
        if (cabeca->primeiro->proximo == NULL)
        {
            cabeca->primeiro->proximo = novo;
            novo->anterior =  cabeca->primeiro->proximo;
        }
        else{
            novo->proximo = NULL;
            insere_final(cabeca, novo);
        }
    }
    printf("Pedido '%s' com tempo de espera de '%d' segundos acaba de chegar.", prato, tempo_fazer);
    return;
}

void gera_pedido(struct gancho_pedidos *cabeca_pedidos)
{
    pthread_t thread_gera_pedido;
    while (1)
    {
        pthread_create(&thread_gera_pedido, NULL, thread_adicionar_prato, (void *)cabeca_pedidos);
        sleep(5);
    }
}

void *thread_adicionar_prato(void* args)
{
    struct gancho_pedidos *cabeca = (struct cabeca *)args;
    int number = rand() % 10;
    insert_prato(number, cabeca);
    return NULL;
}

void ver_pedidos(struct gancho_pedidos *cabeca)
{
    if (cabeca != NULL)
    {
        struct pedidos *aux = cabeca->primeiro;
        while(aux != NULL)
        {
            printw("'%s'\n", aux->prato);
        }
    }
    else{
        printw("Ocorreu um erro inesperado. Reinicie o programa e tente novamente.");
    }
}

void insert_prato(int number, struct gancho_pedidos *head)
{
    if (number == 0)
    {
        adicionar_item_pedido(head, "pao de queijo com linguica", 5);
    }
    else if (number == 1)
    {
        adicionar_item_pedido(head, "broa de milho + cafe", 5);
    }
    else if (number == 2)
    {
        adicionar_item_pedido(head, "biscoito frito de polvilho", 5);
    }
    else if (number == 3)
    {
        adicionar_item_pedido(head, "torresmo com rabada", 3);
    }
    else if (number == 4)
    {
        adicionar_item_pedido(head, "guaranazinho com croquete", 4);
    }
    else if (number == 5)
    {
        adicionar_item_pedido(head, "bolo de milho com cafe coado", 5);
    }
    else if (number == 6)
    {
        adicionar_item_pedido(head, "cafe coado", 2);
    }
    else if (number == 7)
    {
        adicionar_item_pedido(head, "doce de abobora com coco ralado", 6);
    }
    else if (number == 8)
    {
        adicionar_item_pedido(head, "rapadura com goiabada e queijo", 3);
    }
    else if (number == 9)
    {
        adicionar_item_pedido(head, "pamonha e cafe com leite",5);
    }
}

void deletar_item_pedido(struct pedidos *no, struct gancho_pedidos *cabeca)
{
    struct pedidos *aux = cabeca->primeiro;

    if (aux == no)
    {
        if (aux->proximo != NULL)
        {
            cabeca->primeiro = aux->proximo;
            aux->proximo->anterior = cabeca->primeiro;
            free(no);
        }else{
            free(no);
        }
    }
    else if (no->proximo == NULL)
    {
        free(no);
    }
    else{
        while (aux->proximo != no)
        {
            aux = aux->proximo;
        }
        aux->proximo = no->proximo;
        no->proximo->anterior = aux;
        free(no);
    }
    return;
}