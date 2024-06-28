#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "pedidos.h"
#include "lista_encadeada_struct.h"

void *gera_pedidos(void* cabeca)
{
    while (1)
    {
        thread_adicionar_prato(cabeca);
        sleep(1);
    }
}

void thread_adicionar_prato(void* args)
{
    struct gancho *cabeca = (struct gancho *)args;
    int number = rand() % 10;
    insert_prato(number, cabeca);
    return;
}

void printa_tela_pedidos(struct gancho *cabeca)
{
    if (cabeca != NULL)
    {
        int cont = 2;
        struct No *aux = cabeca->primeiro;
        move(0,80);
        printw("No");
        move(1,80);
        printw("------------------------------------");
        while(aux != NULL)
        {
            move(cont,80);
            printw("| id:%d '%s' - '%d' (segs)|\n", aux->numero_pedido,aux->prato, aux->tempo_fazer);
            aux = aux->proximo;
            cont++;
        }
        move(cont + 1, 80);
        printw("------------------------------------");
    }
    else{
        printw("Ocorreu um erro inesperado. Reinicie o programa e tente novamente.");
    }
    refresh();
}

void insert_prato(int number, struct gancho *head)
{
    if (number == 0)
    {
        adicionar_item(head, "pao de queijo com linguica", 5, "pedidos");
    }
    else if (number == 1)
    {
        adicionar_item(head, "broa de milho + cafe", 5, "pedidos");
    }
    else if (number == 2)
    {
        adicionar_item(head, "biscoito frito de polvilho", 5, "pedidos");
    }
    else if (number == 3)
    {
        adicionar_item(head, "torresmo com rabada", 3, "pedidos");
    }
    else if (number == 4)
    {
        adicionar_item(head, "guaranazinho com croquete", 4, "pedidos");
    }
    else if (number == 5)
    {
        adicionar_item(head, "bolo de milho com cafe coado", 5, "pedidos");
    }
    else if (number == 6)
    {
        adicionar_item(head, "cafe coado", 2, "pedidos");
    }
    else if (number == 7)
    {
        adicionar_item(head, "doce de abobora com coco ralado", 6, "pedidos");
    }
    else if (number == 8)
    {
        adicionar_item(head, "rapadura com goiabada e queijo", 3, "pedidos");
    }
    else if (number == 9)
    {
        adicionar_item(head, "pamonha e cafe com leite",5, "pedidos");
    }
    return;
}