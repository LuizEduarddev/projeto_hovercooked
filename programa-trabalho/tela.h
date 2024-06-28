#ifndef TELA_H
#define TELA_H
#define NOME_PRATO 100

typedef struct tela_struct
{
    struct gancho *cabeca_pronto;
    struct gancho *cabeca_preparo;
    struct gancho *cabeca_pedido;
}tela_struct;

void start();
void gera_tela(struct gancho *cabeca_pedidos, struct gancho *cabeca_preparo, struct gancho *cabeca_pronto);
void *thread_func_tela(void* tela_data);
struct tela_struct *create_variable_tela(struct gancho *cabeca_pedidos, struct gancho *cabeca_preparo, struct gancho *cabeca_pronto);

#endif