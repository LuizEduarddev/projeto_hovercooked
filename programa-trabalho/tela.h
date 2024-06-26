#ifndef TELA_H
#define TELA_H
#define NOME_PRATO 100
#include "pronto.h"
#include "pedidos.h"
#include "preparo.h"

typedef struct tela_struct
{
    struct gancho_pronto *cabeca_pronto;
    struct gancho_preparo *cabeca_preparo;
    struct gancho_pedidos *cabeca_pedido;
}tela_struct;

void start();
void gera_tela(struct gancho_pedidos *cabeca_pedidos, struct gancho_preparo *cabeca_preparo, struct gancho_pronto *cabeca_pronto);
void *thread_func_tela(void* tela_data);
struct tela_struct *create_variable_tela(struct gancho_pedidos *cabeca_pedidos, struct gancho_preparo *cabeca_preparo, struct gancho_pronto *cabeca_pronto);

#endif