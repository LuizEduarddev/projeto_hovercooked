#ifndef TELA_H
#define TELA_H
#define NOME_PRATO 100

extern pthread_mutex_t tela_mutex;

typedef struct tela_struct
{
    struct gancho *cabeca_pronto;
    struct gancho *cabeca_preparo;
    struct gancho *cabeca_pedido;
    int bancadas_atuais;
    int bancadas_maximas;
    int cozinheiros_atuais;
}tela_struct;

void start();
void gera_tela(struct gancho *cabeca_pedidos, struct gancho *cabeca_preparo, struct gancho *cabeca_pronto);
void gera_tela_comandos(struct tela_struct *tela_data);
void *thread_func_tela(void* tela_data);
struct tela_struct *create_variable_tela(struct gancho *cabeca_pedidos, struct gancho *cabeca_preparo, struct gancho *cabeca_pronto);
void *pega_comandos(void * tel);
void *thread_timer_function(void *null);
#endif