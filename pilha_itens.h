#ifndef PILHA_ITENS_H
#define PILHA_ITENS_H

#include "item.h"

typedef struct NodoPilha {
    Item *item;
    struct NodoPilha *prox;
} NodoPilha;

typedef struct {
    NodoPilha *topo;
    int quantidade_disponivel; // Mantém o controle exato do estoque 
} PilhaItens;


PilhaItens* criar_pilha();
void adicionar_ao_estoque(PilhaItens *pilha, Item *i);
Item* distribuir_item(PilhaItens *pilha);
void consultar_estoque(PilhaItens *pilha, const char *nome_categoria);
void consumir_item_definitivamente(Item *i);
void liberar_pilha(PilhaItens *pilha);

#endif