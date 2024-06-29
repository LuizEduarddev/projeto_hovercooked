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

void ativar_bancada(struct No *pedidos, struct tela_struct *tela)
{
    tela->cozinheiros_atuais += 1;
    tela->bancadas_atuais += 1;
    deletar_item_pedido(pedidos, tela->cabeca_pedido);
    sleep(pedidos->tempo_fazer);
    adicionar_item(tela->cabeca_preparo, pedidos->prato, pedidos->tempo_fazer, "preparo");
    tela->cozinheiros_atuais -= 1;
    tela->bancadas_atuais -= 1;
    return;
}

void *thread_bancada_func(void *varrer)
{
    int cont = 0;
    struct struct_varrimento *varrimento = (struct struct_varrimento *) varrer;
    struct No *pedidos = varrimento->tela->cabeca_pedido->primeiro;
    while (pedidos != NULL)
    {
        if (pedidos->numero_pedido == varrimento->tecla)
        {
            cont = 1;
            ativar_bancada(pedidos, varrimento->tela);
        }
        pedidos = pedidos->proximo;
    }
    if (cont == 0)
    {
        move(3,0);
        printw("Id de pedido nao encontrado.\n");
    }
}

void seta_cozinheiro_item(struct tela_struct *tela_data, int tecla)
{
    if (tela_data->cozinheiros_atuais == tela_data->bancadas_maximas)
    {
        move(2,0);
        clrtoeol();
        printw("Todos os '%d' cozinheiros estao ocupados. Bancadas restantes '0'.", tela_data->cozinheiros_atuais);
        sleep(2);
        return;
    }
    else{
        pthread_t thread_bancada;
        struct struct_varrimento *varrimento;
        varrimento = (struct struct_varrimento *)malloc(sizeof(struct struct_varrimento));
        if (varrimento != NULL)
        {
            varrimento->tela = tela_data;
            varrimento->tecla = tecla;
            pthread_create(&thread_bancada, NULL, thread_bancada_func, (void *)varrimento);
        }
        else{
            move(3,0);
            printw("Ocorreu um erro durante a instanciacao de 'varrimento'.\n");
            return;
        }
    }
}

void *thread_ver_preparo_func(void *cabeca_preparo)
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
                clrtoeol(); 
                printw("preparados");
                clrtoeol();
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

void preparar_item(struct tela_struct *tela_data)
{
    pthread_t thread_ver_preparo;
    pthread_create(&thread_ver_preparo, NULL, thread_ver_preparo_func, (void *)tela_data->cabeca_preparo);
    int tecla;
    move(0, 30);
    printw("----- Selecione um id de pedido para adicionar a bancada. ------");
    tecla = getch();
    tecla = tecla - '0';
    if (tecla >= 1 && tecla <= 9)
    {
        move(2,0);
        clrtoeol(); 
        printw("tecla %d", tecla);
        seta_cozinheiro_item(tela_data, tecla);

    }
    else{
        move(2,0);
        clrtoeol(); 
        printw("pressione uma tecla entre 1 e 9 para escolher o id de um pedido");
    }
    
    
}
