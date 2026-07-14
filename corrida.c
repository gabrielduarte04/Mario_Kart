#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "corrida.h"

Corrida* criar_corrida(int id, const char *pista, int voltas, int perigo, const char *clima) {
    Corrida *c = (Corrida*) malloc(sizeof(Corrida));
    if (c != NULL) {
        c->id_cadastro = id;
        c->numero_voltas = voltas;
        c->nivel_perigo = perigo;
        
        strncpy(c->nome_pista, pista, sizeof(c->nome_pista) - 1);
        c->nome_pista[sizeof(c->nome_pista) - 1] = '\0';
        
        strncpy(c->condicao_climatica, clima, sizeof(c->condicao_climatica) - 1);
        c->condicao_climatica[sizeof(c->condicao_climatica) - 1] = '\0';
        
        strncpy(c->status, "Aguardando", sizeof(c->status) - 1);
        c->status[sizeof(c->status) - 1] = '\0';
    }
    return c;
}

// Fase de Simulação 
void simular_corrida(Corrida *c, Participante participantes[], int qtd_participantes) {
    printf("\n=== INICIANDO SIMULACAO: %s ===\n", c->nome_pista);
    strncpy(c->status, "Em Andamento", sizeof(c->status) - 1);
    
    srand(time(NULL)); 

    // Cálculo de Desempenho
    for (int i = 0; i < qtd_participantes; i++) {
        Participante *p = &participantes[i];
        
        int bonus_kart = (p->kart->velocidade + p->kart->aceleracao + p->kart->controle) / 3;
        
        int efeito_item;

        if (p->item != NULL) {
            efeito_item = p->item->poder;
        } else {
            efeito_item = 0;
        }
        
        int fator_sorte = rand() % 21; // Sorte aleatória de 0 a 20
        
        p->resultado_final = p->piloto->velBase + bonus_kart + efeito_item + fator_sorte - c->nivel_perigo;
        
        // Simulação de Eventos e Consequências
        if (fator_sorte < 2) { 
            // Azar alto: Destruição
            strncpy(p->kart->status, "Destruido", sizeof(p->kart->status) - 1);
            strncpy(p->piloto->status, "Suspenso", sizeof(p->piloto->status) - 1);
            p->resultado_final -= 50; // Penalidade massiva
            printf("  -> ALERTA: O kart de %s foi destruido na pista!\n", p->piloto->nome);
        } else if (fator_sorte < 5) {
            // Acidente
            strncpy(p->kart->status, "Danificado", sizeof(p->kart->status) - 1);
            strncpy(p->piloto->status, "Acidentado", sizeof(p->piloto->status) - 1);
            p->resultado_final -= 20;
            printf("  -> ALERTA: %s sofreu um acidente.\n", p->piloto->nome);
        }
    }

    //Ordenar o Pódio (Bubble Sort simples pela pontuação do resultado)
    for (int i = 0; i < qtd_participantes - 1; i++) {
        for (int j = 0; j < qtd_participantes - i - 1; j++) {
            if (participantes[j].resultado_final < participantes[j+1].resultado_final) {
                Participante temp = participantes[j];
                participantes[j] = participantes[j+1];
                participantes[j+1] = temp;
            }
        }
    }

    //Resultado Final
    printf("\n--- RESULTADO FINAL ---\n");
    printf("1o Lugar: %s (Trofeu concedido!)\n", participantes[0].piloto->nome);
    participantes[0].piloto->qtdTrofeus++; // Vitória Absoluta
    
    strncpy(c->status, "Finalizada", sizeof(c->status) - 1);
}

void liberar_corrida(Corrida *c) {
    if (c != NULL) free(c);
}