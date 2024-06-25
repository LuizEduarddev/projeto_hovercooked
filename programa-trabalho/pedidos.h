#ifndef PEDIDOS_H
#define PEDIDOS_H
#define NOME_PRATO 100 

typedef struct pedidos
{
    int tempo_fazer;
    char prato[NOME_PRATO];
    struct pedidos* proximo;
    struct pedidos* anterior;
};

typedef struct gancho_pedidos
{
    struct pedidos *primeiro;
};

struct gancho_pedidos* criar_lista_pedidos(void);
void adicionar_item_pedido(struct gancho_pedidos *cabeca, char *prato, int tempo_fazer);
void gera_pedido(struct gancho_pedidos *cabeca_pedidos);
void *thread_adicionar_prato(void* args);
void insert_prato(int number, struct gancho_pedidos *head);
void deletar_item_pedido(struct pedidos *no, struct gancho_pedidos *cabeca);
void ver_pedidos(struct gancho_pedidos *cabeca);
#endif