#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "lista_encadeada_struct.h"
#include "pedidos.h"

int itens_pedidos_totais = 0;

int insere_numero_pedido(struct gancho *cabeca)
{
    if (cabeca->primeiro == NULL)
    {
        return 1;
    }
    else{
        int cont = 0;
        struct No *aux = cabeca->primeiro;
        while (aux != NULL)
        {
            cont++;
            aux = aux->proximo;
        }
        return cont;
    }
}

void adicionar_item(struct gancho *cabeca, char *prato, int tempo_fazer, char *nome_struct) {
    
    if (strcmp(nome_struct, "pedidos") == 0 && itens_pedidos_totais == 10)
    {
        return;
    }
    else if (strcmp(nome_struct, "pedidos") == 0)
    {
        itens_pedidos_totais += 1;
    }
    struct No* novo = (struct No *)malloc(sizeof(struct No));
    if (novo == NULL) {
        fprintf(stderr, "Failed to allocate memory for new pedido\n");
        return;
    }
    if (cabeca->primeiro == NULL) {
        cabeca->primeiro = novo;
    } else {
        insere_final_No(cabeca, novo);
    }
    
    strcpy(novo->nome_struct, nome_struct);
    atualiza_numero(cabeca);
    novo->numero_pedido = insere_numero_pedido(cabeca);
    novo->tempo_fazer = tempo_fazer;
    strcpy(novo->prato, prato);
    novo->anterior = NULL;
    novo->proximo = NULL;
}

struct gancho* criar_lista_No(void)
{
    struct gancho *cabeca = (struct gancho *)(malloc(sizeof(struct gancho)));
    cabeca->primeiro = NULL;
    return cabeca;
}

void insere_final_No(struct gancho *cabeca, struct No *novo) {
    struct No *primaria = cabeca->primeiro;

    while (primaria->proximo != NULL) 
    {
        primaria = primaria->proximo;
    }

    primaria->proximo = novo;
    novo->anterior = primaria;
    novo->proximo = NULL;
}

void atualiza_numero(struct gancho *cabeca)
{
    if (cabeca->primeiro == NULL)
    {
        return;
    }
    else{
        struct No *aux = cabeca->primeiro;
        int cont = 1;
        while (aux != NULL)
        {
            aux->numero_pedido = cont;
            cont++;
            aux = aux->proximo;
        }
    }
}

void deletar_item_pedido(struct No *no, struct gancho *cabeca)
{
    atualiza_numero(cabeca);
    if (strcmp(no->nome_struct, "pedidos") == 0)
    {
        itens_pedidos_totais -= 1;
    }
    struct No *aux = cabeca->primeiro;
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