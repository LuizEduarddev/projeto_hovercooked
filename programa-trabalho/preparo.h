#ifndef PREPARO_H
#define PREPARO_H
#define NOME_PRATO 100 

typedef struct no_preparo
{
    int tempo_fazer;
    char prato[NOME_PRATO];
    struct no_preparo* proximo;
    struct no_preparo* anterior;
};

typedef struct gancho_preparo
{
    struct no_preparo *primeiro;
};

struct gancho_preparo* criar_lista_preparo(void);
void insere_final_preparo(struct gancho_preparo *cabeca, struct no_preparo *novo);
void adicionar_item_preparo(struct gancho_preparo *cabeca, char *prato, int tempo_fazer);
void deletar_item_preparo(struct no_preparo *no, struct gancho_preparo *cabeca);
#endif