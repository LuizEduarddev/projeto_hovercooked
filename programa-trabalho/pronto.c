#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "pronto.h"
#include "lista_encadeada_struct.h"

void ver_pronto_func__(struct gancho *cabeca)
{
    if (cabeca != NULL)
    {
        if (cabeca->primeiro != NULL)
        {
            int cont = 6;
            struct No *aux = cabeca->primeiro;
            move(4,120);
            printw("pronto");
            move(5,120);
            printw("------------------------------------");
            while(aux != NULL)
            {
                move(cont,120);
                printw("| id:%d '%s' - '%d' (segs)|\n", aux->numero_pedido, aux->prato, aux->tempo_fazer);
                aux = aux->proximo;
                cont++;
            }
            move(cont + 1, 120);
            printw("------------------------------------");
        }else{
            move(4, 120);
            printw("pronto");
            move(5,120);
            printw("nenhum pedido pronto ainda");
        }
    }
    else{
        printw("Ocorreu um erro inesperado. Reinicie o programa e tente novamente.");
    }
    refresh();
    return NULL;
}
