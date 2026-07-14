#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "avl_pilotos.h"
#include "corrida.h" 

// Operações do Campeonato 
void atualizar_pontuacoes(Participante participantes[], int qtd_participantes);
void exibir_ranking_completo(NoAVL *raiz_pilotos);
void exibir_top_10(NoAVL *raiz_pilotos);
void determinar_campeao(NoAVL *raiz_pilotos);

#endif