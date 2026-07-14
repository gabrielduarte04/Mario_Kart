#include <stdio.h>
#include <stdlib.h>
#include "pilha_itens.h"

PilhaItens* criar_pilha() {
    PilhaItens *pilha = (PilhaItens*) malloc(sizeof(PilhaItens));
    if (pilha != NULL) {
        pilha->topo = NULL;
        pilha->quantidade_disponivel = 0;
    }
    return pilha;
}

// Adicionar itens ao estoque ou receber devolvidos
void adicionar_ao_estoque(PilhaItens *pilha, Item *i) {
    if (pilha == NULL || i == NULL) return;
    
    NodoPilha *novo_nodo = (NodoPilha*) malloc(sizeof(NodoPilha));
    if (novo_nodo != NULL) {
        novo_nodo->item = i;
        novo_nodo->prox = pilha->topo; // O novo nó aponta para o antigo topo
        pilha->topo = novo_nodo;       // O topo passa a ser o novo nó
        pilha->quantidade_disponivel++;
    }
}

// Distribuir itens para corridas
Item* distribuir_item(PilhaItens *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("Aviso: Estoque vazio! Impossivel distribuir.\n");
        return NULL; // O sistema impede o uso de itens que não existem
    }
    
    NodoPilha *nodo_removido = pilha->topo;
    Item *item_distribuido = nodo_removido->item;
    
    pilha->topo = nodo_removido->prox; // O topo desce para o próximo nó
    pilha->quantidade_disponivel--;
    
    free(nodo_removido); // Libera o Nodo, mas o Item continua existindo na corrida
    return item_distribuido;
}

//Visualizar itens disponíveis 
void consultar_estoque(PilhaItens *pilha, const char *nome_categoria) {
    if (pilha != NULL) {
        printf("Estoque de %s: %d unidades disponiveis.\n", 
               nome_categoria, pilha->quantidade_disponivel);
    }
}

// Remover itens consumidos
void consumir_item_definitivamente(Item *i) {
    // Quando o item é gasto na corrida, ele apenas sofre o free() final.
    // Como ele já foi retirado da Pilha pelo 'distribuir_item',
    // não existe o risco de estar em dois lugares ao mesmo tempo
    liberar_item(i);
}

// Limpeza da memória ao encerrar o sistema
void liberar_pilha(PilhaItens *pilha) {
    if (pilha != NULL) {
        NodoPilha *atual = pilha->topo;
        while (atual != NULL) {
            NodoPilha *temp = atual;
            atual = atual->prox;
            liberar_item(temp->item);
            free(temp);
        }
        free(pilha);
    }
}