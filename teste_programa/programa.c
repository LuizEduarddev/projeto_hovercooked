#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <ncurses.h>
#include <string.h>

#define max_cozinheiros = 2;
#define max_bancadas = 2;

typedef struct {
    int id_pedido;
    int tempo_fazer;
    char nome_prato[100];
}Prato;

typedef struct{

}Cozinheiro;