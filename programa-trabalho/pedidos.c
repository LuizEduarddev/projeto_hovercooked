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

void gera_pedido(void)
{

    pthread_t thread_gera_pedido;
    struct gancho_pedidos *cabeca_pedidos = criar_lista_pedidos();
    while (1)
    {
        pthread_create(&thread_gera_pedido, NULL, thread_adicionar_prato, (void *)cabeca_pedidos);
        sleep(5);
    }
}

void *thread_adicionar_prato(void* args)
{
    struct gancho *cabeca = (struct cabeca *)args;
    int number = rand() % 10;
    insert_prato(number, cabeca);
    return NULL;
}

void insert_prato(int number, struct gancho *head)
{
    if (number == 0)
    {
        adicionar_item_preparo(head, "pao de queijo com linguica", 5);
    }
    else if (number == 1)
    {
        adicionar_item_preparo(head, "broa de milho + cafe", 5);
    }
    else if (number == 2)
    {
        adicionar_item_preparo(head, "biscoito frito de polvilho", 5);
    }
    else if (number == 3)
    {
        adicionar_item_preparo(head, "torresmo com rabada", 3);
    }
    else if (number == 4)
    {
        adicionar_item_preparo(head, "guaranazinho com croquete", 4);
    }
    else if (number == 5)
    {
        adicionar_item_preparo(head, "bolo de milho com cafe coado", 5);
    }
    else if (number == 6)
    {
        adicionar_item_preparo(head, "cafe coado", 2);
    }
    else if (number == 7)
    {
        adicionar_item_preparo(head, "doce de abobora com coco ralado", 6);
    }
    else if (number == 8)
    {
        adicionar_item_preparo(head, "rapadura com goiabada e queijo", 3);
    }
    else if (number == 9)
    {
        adicionar_item_preparo(head, "pamonha e cafe com leite",5);
    }
}