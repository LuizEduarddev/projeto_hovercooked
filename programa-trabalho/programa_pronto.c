#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define NOME_PRATO 100

typedef struct no
{
    int tempo_fazer;
    char prato[NOME_PRATO];
    struct no* proximo;
    struct no* anterior;
};

typedef struct gancho
{
    struct no *primeiro;
};

struct gancho* criar_lista(void)
{
    struct gancho *cabeca = (struct gancho *)(malloc(sizeof(struct gancho)));
    cabeca->primeiro = NULL;
    return cabeca;
}

void insertPrato(int number, struct gancho *head)
{
    if (number == 0)
    {
        adicionar_item(head, "pao de queijo com linguica", 5);
    }
    else if (number == 1)
    {
        adicionar_item(head, "broa de milho + cafe", 5);
    }
    else if (number == 2)
    {
        adicionar_item(head, "biscoito frito de polvilho", 5);
    }
    else if (number == 3)
    {
        adicionar_item(head, "torresmo com rabada", 3);
    }
    else if (number == 4)
    {
        adicionar_item(head, "guaranazinho com croquete", 4);
    }
    else if (number == 5)
    {
        adicionar_item(head, "bolo de milho com cafe coado", 5);
    }
    else if (number == 6)
    {
        adicionar_item(head, "cafe coado", 2);
    }
    else if (number == 7)
    {
        adicionar_item(head, "doce de abobora com coco ralado", 6);
    }
    else if (number == 8)
    {
        adicionar_item(head, "rapadura com goiabada e queijo", 3);
    }
    else if (number == 9)
    {
        adicionar_item(head, "pamonha e cafe com leite",5);
    }
}

void insere_final(struct gancho *cabeca, struct no *novo)
{
    struct no* aux = cabeca->primeiro;
    struct no* atual = novo;

    while (aux->proximo != NULL)
    {
        aux = aux->proximo;
    }

    aux->proximo = novo;
    novo->anterior = aux;
    return;

}

void adicionar_item(struct gancho *cabeca, char *prato, int tempo_fazer)
{
    struct no* novo = (struct no *)(malloc(sizeof(struct no)));
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
}

void gera_pedido(struct gancho *cabeca)
{

    pthread_t thread_gera_pedido;
    int cont = 0;
    while (cont != 10)
    {
        pthread_create(&thread_gera_pedido, NULL, thread_adicionar_prato, (void *)cabeca);
        cont++; 
    }
}

void *thread_adicionar_prato(void* args)
{
    struct gancho *cabeca = (struct cabeca *)args;
    int number = rand() % 10;
    insertPrato(number, cabeca);
    return NULL;
}

void printarLista(struct gancho *cabeca) {
    struct no *atual = cabeca->primeiro;
    while (atual != NULL)
    {
        printf("pedido '%s' com tempo de espera de '%d' segundos", atual->prato, atual->tempo_fazer);
    }
    return;
}

int main() {
    struct no* cabeca = criar_lista();
    int vitoria = 0;
    gera_pedido(cabeca);
    
    while (vitoria == 0)
    {
        // pthread_t pega_escolha_usuario;
        // pthread_create(&pega_escolha_usuario, NULL, thread_escolha, NULL);
        sleep(5);
        printarLista(cabeca);
    }

    return 0;
}
