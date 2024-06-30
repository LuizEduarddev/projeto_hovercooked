#ifndef __STRUCT_PROGRAMA_H
#define __STRUCT_PROGRAMA_H
#define NOME_PRATO 100

extern int semaforo;
typedef struct No
{
    char nome_struct[NOME_PRATO];
    int numero_pedido;
    int tempo_fazer;
    char prato[NOME_PRATO];
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct gancho
{
    struct No *primeiro;
} gancho;

struct gancho* criar_lista_No(void);
void atualiza_numero(struct gancho *cabeca);
void adicionar_item(struct gancho *cabeca, char *prato, int tempo_fazer, char *nome_struct);
void insere_final_No(struct gancho *cabeca, struct No *novo);
void deletar_item_pedido(struct No *no, struct gancho *cabeca);

#endif
