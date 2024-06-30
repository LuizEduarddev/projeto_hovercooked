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

void ver_preparo_func__(struct gancho *cabeca)
{
    if (cabeca != NULL)
    {
        if (cabeca->primeiro != NULL)
        {
            int cont = 6;
            int conta_linha = 1;
            struct No *aux = cabeca->primeiro;
            move(4,60);
            printw("preparados");
            move(5,60);
            printw("------------------------------------");
            while(aux != NULL)
            {
                if (conta_linha >= 10)
                {
                    move(cont,60);
                    printw("+ %d pedidos......\n", conta_linha);
                    aux = aux->proximo;
                }
                else{
                    move(cont,60);
                    printw("| id:%d '%s' - '%d' (segs)|\n", aux->numero_pedido,aux->prato, aux->tempo_fazer);
                    aux = aux->proximo;
                    cont++;
                }
                conta_linha++;
            }
            move(cont + 1, 60);
            printw("------------------------------------");
        }
        else{
            move(4,60);
            printw("preparados");
            move(5,60);
            printw("Nenhum pedido preparado ainda.");
        }
    }
    else{
        printw("Ocorreu um erro inesperado. Reinicie o programa e tente novamente.");
    }
    refresh();
}