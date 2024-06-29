#ifndef __JOGO_H
#define __JOGO_H

typedef struct struct_varrimento
{
    struct tela_struct *tela;
    int tecla;
}struct_varrimento;

void ativar_bancada(struct No *pedidos, struct tela_struct *tela);
void *thread_bancada_func(void *varrer);
void seta_cozinheiro_item(struct tela_struct *tela_data, int tecla);
void *thread_ver_preparo_func(void *cabeca_preparo);
void preparar_item(struct tela_struct *tela_data);

#endif