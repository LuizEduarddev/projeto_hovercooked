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

void ativar_bancada(struct No *no_retirar, struct gancho *cabeca_retirar, struct gancho *cabeca_adicionar, struct tela_struct *tela)
{
    int tempo_fazer = no_retirar->tempo_fazer;
    char *prato = no_retirar->prato;
    tela->cozinheiros_atuais += 1;
    tela->bancadas_atuais += 1;
    deletar_item_pedido(no_retirar, cabeca_retirar);
    sleep(tempo_fazer);
    adicionar_item(cabeca_adicionar, prato, tempo_fazer, "");
    tela->cozinheiros_atuais -= 1;
    tela->bancadas_atuais -= 1;
    return;
}

void *thread_bancada_func(void *varrer)
{
    int cont = 0;
    struct struct_varrimento *varrimento = (struct struct_varrimento *) varrer;
    struct No *no_retirar = varrimento->cabeca_retirar->primeiro;
    while (no_retirar != NULL)
    {
        if (no_retirar->numero_pedido == varrimento->tecla)
        {
            cont = 1;
            ativar_bancada(no_retirar, varrimento->cabeca_retirar ,varrimento->cabeca_adicionar, varrimento->tela);
        }
        no_retirar = no_retirar->proximo;
    }
    /*
    if (cont == 0)
    {
        move(3,0);
        printw("Id de pedido nao encontrado.\n");
    }
    */
}

void seta_cozinheiro_item(struct gancho *cabeca_retirar, struct gancho *cabeca_adicionar, int tecla, struct tela_struct *tela_data)
{
    if (tela_data->cozinheiros_atuais == tela_data->bancadas_maximas)
    {
        move(1,0);
        clrtoeol();
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
            varrimento->cabeca_retirar = cabeca_retirar;
            varrimento->cabeca_adicionar = cabeca_adicionar;
            varrimento->tecla = tecla;
            pthread_create(&thread_bancada, NULL, thread_bancada_func, (void *)varrimento);
        }
    }
}

void preparar_item(struct gancho *cabeca_retirar, struct gancho *cabeca_adicionar, struct tela_struct *tela_data)
{   
    int tecla;

    pthread_mutex_lock(&tela_mutex);
    move(0, 0);
    clrtoeol();
    printw("----- Selecione um id de pedido para adicionar a bancada. ------");
    tecla = getch();
    tecla = tecla - '0';
    if (tecla >= 1 && tecla <= 9)
    {
        seta_cozinheiro_item(cabeca_retirar, cabeca_adicionar, tecla, tela_data);
    }
    else {
        move(2, 0);
        clrtoeol(); 
        printw("tecla invalida");
    }
    pthread_mutex_unlock(&tela_mutex);
    clear();
}
