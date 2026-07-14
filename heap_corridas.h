#ifndef HEAP_CORRIDAS_H
#define HEAP_CORRIDAS_H

#include "corrida.h"

typedef struct {
    Corrida **vetor;
    int tamanho;
    int capacidade;
} MaxHeap;

MaxHeap* criar_heap(int capacidade);
void inserir_corrida_heap(MaxHeap *h, Corrida *c);
Corrida* extrair_proxima_corrida(MaxHeap *h);
void visualizar_proximas_corridas(MaxHeap *h);
void liberar_heap(MaxHeap *h);

#endif