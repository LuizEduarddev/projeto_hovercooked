#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include "pronto.h" 
#include "preparo.h"
#include "pedidos.h"
#include "tela.h"
#include "lista_encadeada_struct.h"
#include "jogo.h"

void varre_lista(struct gancho *cabeca_pedido, int tecla)
{
    struct No *aux = cabeca_pedido->primeiro;
    while (aux != NULL)
    {
        if (aux->numero_pedido == tecla)
        {
            pthread_t thread_bancada;
            
        }
        aux = aux->proximo;
    }
}

void seta_cozinheiro_item(struct tela_struct *tela_data, int tecla)
{
    if (tela_data->cozinheiros_atuais == tela_data->cozinheiros_maximos)
    {
        move(0,0);
        printw("Todos os '%d' cozinheiros estao ocupados. Bancadas restantes '0'.", tela_data->cozinheiros_atuais);
        sleep(2);
        return;
    }
    else{
        varre_lista(tela_data->cabeca_pedido, tecla);
    }
}

int preparar_item(struct tela_struct *tela_data)
{
    int tecla;
    move(0, 0);
    printw("Selecione um id de pedido para adicionar a bancada.");
    move(1,0);
    printw("Para retornar para o menu aperte 'q' ou 'f4'.");
    while (tecla != 'q' && tecla != KEY_F(4)) 
    {
        if (isdigit(tecla)) 
        {
            move(2,0);
            seta_cozinheiro_item(tela_data, tecla);
        } else 
        {
            move(2,0);
            printw("Invalid key. Please press a number key.\n");
        }
    }
}
