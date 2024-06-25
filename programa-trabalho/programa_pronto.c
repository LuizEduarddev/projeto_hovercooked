#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#define NOME_PRATO 100 

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
    struct no_preparo* cabeca_preparo = criar_lista_preparo();
    struct no_pronto* cabeca_pronto = criar_lista_pronto();
    int vitoria = 0;
    int vida = 5;
    gera_pedido();

    while (vida > 0)
    {
        pega_escolha(cabeca);
    }

    return 0;
}
