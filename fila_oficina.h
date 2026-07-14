#ifndef FILA_OFICINA_H
#define FILA_OFICINA_H

#include "kart.h"

typedef struct NoFila {
    Kart *kart;
    struct NoFila *prox;
} NoFila;


typedef struct {
    NoFila *frente_destruidos;
    NoFila *tras_destruidos;
    
    NoFila *frente_danificados;
    NoFila *tras_danificados;
} Oficina;


Oficina* criar_oficina();
void registrar_kart_manutencao(Oficina *oficina, Kart *k);
Kart* iniciar_reparo(Oficina *oficina);
void consultar_fila(Oficina *oficina);
void liberar_oficina(Oficina *oficina);

#endif