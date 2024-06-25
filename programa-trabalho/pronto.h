#ifndef PRONTO_H
#define PRONTO_H

#define NOME_PRATO 100 

typedef struct no_pronto
{
    int tempo_fazer;
    char prato[NOME_PRATO];
    struct no_pronto* proximo;
    struct no_pronto* anterior;
};

typedef struct gancho_pronto
{
    struct no_pronto *primeiro;
};

struct gancho_pronto* criar_lista_pronto(void);
void insere_final_pronto(struct gancho_pronto *cabeca, struct no_pronto *novo);
void adicionar_item_pronto(struct gancho_pronto *cabeca, char *prato, int tempo_fazer);
void deletar_item_pronto(struct no_pronto *no, struct gancho_pronto *cabeca);
#endif