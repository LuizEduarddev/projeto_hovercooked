#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#define NOME_PRATO 100

pthread_t bancadas[2];

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
    printf("Pedido '%s' com tempo de espera de '%d' segundos acaba de chegar.", prato, tempo_fazer);
    return;
}

void *thread_adicionar_prato(void* args)
{
    struct gancho *cabeca = (struct cabeca *)args;
    int number = rand() % 10;
    insertPrato(number, cabeca);
    return NULL;
}

void gera_pedido(struct gancho *cabeca)
{

    pthread_t thread_gera_pedido;
    int cont = 0;
    while (cont <= 10)
    {
        pthread_create(&thread_gera_pedido, NULL, thread_adicionar_prato, (void *)cabeca);
        cont++; 
    }
}

void ver_bancadas(void)
{
    int cont = 0;
    for (int i=0; i < 2; i++)
    {
        if (bancadas[i] == NULL)
        {
            cont++;
        }
        else{
            printf("Bancada '%d' disponivel.", i + 1);
        }
    }
    if (cont == 2)
    {
        printf("Todas as bancadas estão em uso no momento. Assim que uma for liberada, você será avisado.");
    }
    return;
}

void inserir_bancada(int num)
{
    if (bancadas[num] == NULL)
    {
        
    }
}

void selecionar_bancada()
{
    int tecla;
    keypad(stdscr, TRUE);
    while (tecla != 'q' && tecla != KEY_F(4))
    {
        tecla = getch();
        switch (tecla)
        {
        case '1':
            inserir_bancada(0);
            break;
        case '2':
            inserir_bancada(1);
            break;
        default:
            break;
        }
    }
}

void *thread_escolha_usuario(void* cabeca)
{
    int tecla;
    keypad(stdscr, TRUE);
    while (tecla != 'q' && tecla != KEY_F(4))
    {
        tecla = getch();
        switch (tecla)
        {
        case '1':
            ver_bancadas();
            break;
        case '2':
            selecionar_bancada();
            break;
        default:
            break;
        }
    }
}

void pega_escolha(struct gancho *cabeca)
{
    pthread_t esccolha_usuario;
    pthread_create(&esccolha_usuario, NULL, thread_escolha_usuario, (void* )cabeca);
}

int main() {
    struct no* cabeca = criar_lista();
    int vitoria = 0;
    int vida = 5;
    gera_pedido(cabeca);

    while (vida > 0)
    {
        pega_escolha(cabeca);
    }

    return 0;
}
