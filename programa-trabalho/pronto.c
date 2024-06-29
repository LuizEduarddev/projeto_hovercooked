#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "pronto.h"
#include "lista_encadeada_struct.h"

void *thread_ver_pronto_func(void *cabeca_preparo)
{
    struct gancho *cabeca = (struct gancho *)cabeca_preparo;
    if (cabeca != NULL)
    {
        while(1)
        {
            struct No *aux = cabeca->primeiro;
            int cont = 1;
            move(9,0);
            clrtoeol();
            while(aux != NULL)
            {
                printw(" --------------- ");
                move(10,0);
                clrtoeol();
                printw("| %d  - pedidos. |", cont);
                aux = aux->proximo;
                cont++;
            }
            move(11, 0);
            clrtoeol();
            printw(" --------------- ");
        }
    }
    else{
        printw("Ocorreu um erro inesperado. Reinicie o programa e tente novamente.");
    }
    refresh();
}

void *thread_ver_pronto_func__(void *cabeca_preparo)
{
    struct gancho *cabeca = (struct gancho *)cabeca_preparo;
    if (cabeca != NULL)
    {
        while (1)
        {
            if (cabeca->primeiro != NULL)
            {
                int cont = 6;
                struct No *aux = cabeca->primeiro;
                move(4,60);
                //clrtoeol(); 
                printw("preparados");
                //clrtoeol();
                move(5,60);
                printw("------------------------------------");
                while(aux != NULL)
                {
                    move(cont,60);
                    printw("| id:%d '%s' - '%d' (segs)|\n", aux->numero_pedido,aux->prato, aux->tempo_fazer);
                    aux = aux->proximo;
                    cont++;
                }
                move(cont + 1, 60);
                printw("------------------------------------");
            }else{
                move(4, 60);
                printw("preparados");
                move(5,60);
                printw("nenhum pedido preparado ainda");
            }
        }
    }
    else{
        printw("Ocorreu um erro inesperado. Reinicie o programa e tente novamente.");
    }
    refresh();
}