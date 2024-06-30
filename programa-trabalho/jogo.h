#ifndef __JOGO_H
#define __JOGO_H

typedef struct struct_varrimento
{
    struct tela_struct *tela;
    struct gancho *cabeca_retirar;
    struct gancho *cabeca_adicionar;
    int tecla;
}struct_varrimento;

void ativar_bancada(struct No *no_retirar, struct gancho *cabeca_retirar, struct gancho *cabeca_adicionar, struct tela_struct *tela);
void *thread_bancada_func(void *varrer);
void seta_cozinheiro_item(struct gancho *cabeca_retirar, struct gancho *cabeca_adicionar, int tecla, struct tela_struct *tela_data);
void preparar_item(struct gancho *cabeca_retirar, struct gancho *cabeca_adicionar, struct tela_struct *tela_data);

#endif