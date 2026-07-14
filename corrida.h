#ifndef CORRIDA_H
#define CORRIDA_H

#include "pilotos.h"
#include "kart.h"
#include "item.h"

typedef struct {
    int id_cadastro; // Usado como critério de desempate (ordem de chegada) 
    char nome_pista[50];
    int numero_voltas;
    int nivel_perigo; // De 1 a 100
    char condicao_climatica[30];
    char status[20];
} Corrida;

// Estrutura de apoio para agrupar as entidades durante a simulação
typedef struct {
    Piloto *piloto;
    Kart *kart;
    Item *item;
    int resultado_final; 
} Participante;

Corrida* criar_corrida(int id, const char *pista, int voltas, int perigo, const char *clima);
void simular_corrida(Corrida *c, Participante participantes[], int qtd_participantes);
void liberar_corrida(Corrida *c);

#endif