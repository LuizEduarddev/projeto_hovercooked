#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "pronto.h"

struct gancho_pronto* criar_lista_pronto(void)
{
    struct gancho_pronto *cabeca = (struct gancho_pronto *)(malloc(sizeof(struct gancho_pronto)));
    cabeca->primeiro = NULL;
    return cabeca;
}

void insere_final(struct gancho_pronto *cabeca, struct no_pronto *novo)
{
    struct no_pronto* aux = cabeca->primeiro;
    struct no_pronto* atual = novo;

    while (aux->proximo != NULL)
    {
        aux = aux->proximo;
    }

    aux->proximo = novo;
    novo->anterior = aux;
    return;
}

void adicionar_item_preparo(struct gancho_pronto *cabeca, char *prato, int tempo_fazer)
{
    struct no_pronto* novo = (struct no_pronto *)(malloc(sizeof(struct no_pronto)));
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