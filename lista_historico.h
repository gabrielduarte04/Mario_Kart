#ifndef LISTA_HISTORICO_H
#define LISTA_HISTORICO_H

#include "corrida.h"

// Estrutura para salvar a corrida finalizada
typedef struct {
    char nome_pista[50];
    char vencedor[50];
    int total_acidentes;
    char participantes[12][50]; // Até 12 pilotos por corrida
    int qtd_participantes;
} RegistroCorrida;

// Utilização do alias Nodo para a Lista Dupla
typedef struct Nodo {
    RegistroCorrida dados;
    struct Nodo *anterior;
    struct Nodo *proximo;
} Nodo;

// Estrutura controladora do histórico
typedef struct {
    Nodo *inicio;
    Nodo *fim;
} Historico;


Historico* criar_historico();
void registrar_corrida_historico(Historico *h, Corrida *c, Participante partes[], int qtd);
void navegar_historico(Historico *h);



void exibir_ranking_vitorias(Historico *h);
void exibir_pistas_com_mais_acidentes(Historico *h);
void exibir_piloto_com_mais_participacoes(Historico *h);

void liberar_historico(Historico *h);

#endif