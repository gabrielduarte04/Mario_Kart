#include <stdio.h>
#include <stdlib.h>
#include "heap_corridas.h"

MaxHeap* criar_heap(int capacidade) {
    MaxHeap *h = (MaxHeap*) malloc(sizeof(MaxHeap));
    if (h != NULL) {
        h->capacidade = capacidade;
        h->tamanho = 0;
        h->vetor = (Corrida**) malloc(capacidade * sizeof(Corrida*));
    }
    return h;
}

// Lógica de comparação
static int comparar_prioridade(Corrida *a, Corrida *b) {
    if (a->nivel_perigo > b->nivel_perigo) return 1;
    if (a->nivel_perigo < b->nivel_perigo) return -1;
    
    // Desempate: Se o perigo for igual, a mais antiga (menor ID) tem prioridade
    if (a->id_cadastro < b->id_cadastro) return 1;
    if (a->id_cadastro > b->id_cadastro) return -1;
    
    return 0;
}

static void trocar(Corrida **a, Corrida **b) {
    Corrida *temp = *a;
    *a = *b;
    *b = temp;
}

// Sobe o nó recém inserido até encontrar seu lugar
static void subir_heap(MaxHeap *h, int indice) {
    int pai = (indice - 1) / 2;
    if (indice > 0 && comparar_prioridade(h->vetor[indice], h->vetor[pai]) > 0) {
        trocar(&(h->vetor[indice]), &(h->vetor[pai]));
        subir_heap(h, pai);
    }
}

// Desce a raiz após uma retirada para manter o Max-Heap
static void descer_heap(MaxHeap *h, int indice) {
    int maior = indice;
    int esq = 2 * indice + 1;
    int dir = 2 * indice + 2;

    if (esq < h->tamanho && comparar_prioridade(h->vetor[esq], h->vetor[maior]) > 0) {
        maior = esq;
    }
    if (dir < h->tamanho && comparar_prioridade(h->vetor[dir], h->vetor[maior]) > 0) {
        maior = dir;
    }

    if (maior != indice) {
        trocar(&(h->vetor[indice]), &(h->vetor[maior]));
        descer_heap(h, maior);
    }
}

// Cadastro de Nova Corrida
void inserir_corrida_heap(MaxHeap *h, Corrida *c) {
    if (h->tamanho == h->capacidade) {
        printf("Aviso: Capacidade maxima da Central de Corridas atingida.\n");
        return;
    }
    h->vetor[h->tamanho] = c;
    subir_heap(h, h->tamanho);
    h->tamanho++;
}

//Iniciar a próxima corrida (Raiz do Heap) 
Corrida* extrair_proxima_corrida(MaxHeap *h) {
    if (h->tamanho <= 0) return NULL;
    if (h->tamanho == 1) {
        h->tamanho--;
        return h->vetor[0];
    }

    Corrida *raiz = h->vetor[0];
    h->vetor[0] = h->vetor[h->tamanho - 1]; // Pega o último nó e coloca no topo
    h->tamanho--;
    descer_heap(h, 0); // Reorganiza a árvore

    return raiz;
}

// Visualizar as próximas corridas programada
void visualizar_proximas_corridas(MaxHeap *h) {
    if (h->tamanho == 0) {
        printf("Nenhuma corrida pendente na Central.\n");
        return;
    }
    printf("--- PROXIMAS CORRIDAS (Ordem de Prioridade) ---\n");
    for (int i = 0; i < h->tamanho; i++) {
        printf(" %d. %s (Perigo: %d)\n", i+1, h->vetor[i]->nome_pista, h->vetor[i]->nivel_perigo);
    }
}

void liberar_heap(MaxHeap *h) {
    if (h != NULL) {
        for (int i = 0; i < h->tamanho; i++) {
            liberar_corrida(h->vetor[i]);
        }
        free(h->vetor);
        free(h);
    }
}