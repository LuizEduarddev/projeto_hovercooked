#ifndef PEDIDOS_H
#define PEDIDOS_H
#define NOME_PRATO 100 
#include "lista_encadeada_struct.h"

void thread_adicionar_prato(void* args);
void insert_prato(int number, struct gancho *head);
void deletar_item_pedido(struct No *no, struct gancho *cabeca);
void printa_tela_pedidos(struct gancho *cabeca);
void *gera_pedidos(void* cabeca);
void mostra_qntd_pedidos(struct gancho *cabeca);
#endif