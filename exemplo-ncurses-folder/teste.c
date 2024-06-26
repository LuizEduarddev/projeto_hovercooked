#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

void imprime_conteudo(int tipo)
{
    if (tipo == 1)
    {
        printw("Olá, como vai?");
    }
    else{
        printw("Oi, eu sou o Goku!");
    }
    refresh();
}

int main()
{
    int tecla;
    initscr(); // Inicializa a tela (posição atual é (0, 0))
    raw();    // Não precisa esperar uma quebra de linha
    noecho(); // O que for digitado não aparece na tela
    keypad(stdscr, TRUE); // Teclas especiais como F1, F2, etc..

    printw("Iniciando...");
    refresh(); 
    sleep(1);

    printw("Pressione 'q' para sair...");

    move(0, 0);
    printw(" - Digite 1, 2, q ou F4: ");
    do {
        tecla = getch();
        switch (tecla) {
            case '1':
                imprime_conteudo(1);
                break;
            case '2':
                imprime_conteudo(2);
                break;
            case KEY_F(4):
                move(8, 0);
                printw("Tecla F4 foi pressionada.. saindo");
                refresh();
                sleep(1);
            case 'q':
            default:
                break;
        }
    } while (tecla != 'q' && tecla != KEY_F(4));

    // Desabilitando tudo que foi habilitado antes de sair, para não deixar o
    // terminal em estado diferente do anterior à execução
    keypad(stdscr, FALSE);
    noraw();
    echo();

    endwin();

    printf("Termino da execucao\n");

    return 0;
}
