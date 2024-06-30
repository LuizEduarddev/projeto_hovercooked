#ifndef JOGO_H
#define JOGO_H

#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define GAME_DURATION 60

extern bool game_over;
extern bool game_won;
extern time_t start_time, current_time;
extern pthread_mutex_t tela_mutex;
extern volatile int jogo_ativo;

struct tela_struct {
    struct gancho *cabeca_pedido;
    struct gancho *cabeca_preparo;
    struct gancho *cabeca_pronto;
    int bancadas_maximas;
    int bancadas_atuais;
    int cozinheiros_atuais;
};

void start();
struct tela_struct *create_variable_tela(struct gancho *cabeca_pedidos, struct gancho *cabeca_preparo, struct gancho *cabeca_pronto);
void gera_tela(struct gancho *cabeca_pedidos, struct gancho *cabeca_preparo, struct gancho *cabeca_pronto);
void encerra_jogo();
void gera_tela_comandos(struct tela_struct *tela_data);

void *pega_comandos(void *tel);
void *thread_func_tela(void *tel);

#endif // JOGO_H
