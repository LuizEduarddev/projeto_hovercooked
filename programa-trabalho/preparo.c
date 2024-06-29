#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "preparo.h"
#include "lista_encadeada_struct.h"
#include "jogo.h"

void *thread_ver_preparo_func(void *cabeca_preparo)
{
    struct gancho *cabeca = (struct gancho *)cabeca_preparo;
    if (cabeca != NULL)
    {
        while (1)
        {
            struct No *aux = cabeca->primeiro;
            int cont = 1;
            move(6,0);
            clrtoeol();
            while(aux != NULL)
            {
                printw(" --------------- ");
                move(7,0);
                clrtoeol();
                printw("| %d  - pedidos. |", cont);
                aux = aux->proximo;
                cont++;
            }
            move(8, 0);
            clrtoeol();
            printw(" --------------- ");
        }
    }
    else{
        printw("Ocorreu um erro inesperado. Reinicie o programa e tente novamente.");
    }
    refresh();
}

void *thread_ver_preparo_func__(void *cabeca_preparo)
{
    struct gancho *cabeca = (struct gancho *)cabeca_preparo;
    if (cabeca != NULL)
    {
        int cont = 6;
        int conta_linha = 1;
        struct No *aux = cabeca->primeiro;
        move(4,0);
        printw("pedidos chegando");
        move(5,0);
        printw("------------------------------------");
        while(aux != NULL)
        {
            if (conta_linha >= 10)
            {
                move(cont,0);
                printw("+ %d pedidos......\n", conta_linha);
                aux = aux->proximo;
            }
            else{
                move(cont,0);
                printw("| id:%d '%s' - '%d' (segs)|\n", aux->numero_pedido,aux->prato, aux->tempo_fazer);
                aux = aux->proximo;
                cont++;
            }
            conta_linha++;
        }
        move(cont + 1, 0);
        printw("------------------------------------");
    }
    else{
        printw("Ocorreu um erro inesperado. Reinicie o programa e tente novamente.");
    }
    refresh();
}