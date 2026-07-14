#include <stdio.h>
#include <stdlib.h>
#include "campeonato.h"

// Operação: Atualizar pontuações de acordo com a tabela oficial [cite: 191, 196]
void atualizar_pontuacoes(Participante participantes[], int qtd_participantes) {
    // A tabela de pontos: 1º=15, 2º=12, 3º=10, 4º=8, 5º=6 
    int pontos[] = {15, 12, 10, 8, 6}; 
    
    printf("\n--- DISTRIBUICAO DE PONTOS DA CORRIDA ---\n");
    for (int i = 0; i < qtd_participantes; i++) {
        int pontos_ganhos = 0;
        
        // Apenas os 5 primeiros recebem pontos
        if (i < 5) {
            pontos_ganhos = pontos[i];
        }
        
        participantes[i].piloto->pontuacao_campeonato += pontos_ganhos;
        
        if (pontos_ganhos > 0) {
            printf("%do Lugar: %s recebeu %d pontos.\n", i + 1, participantes[i].piloto->nome, pontos_ganhos);
        }
    }
}

// Funções auxiliares para extrair os pilotos da árvore para um vetor
static int contar_pilotos(NoAVL *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar_pilotos(raiz->esquerda) + contar_pilotos(raiz->direita);
}

static void extrair_pilotos_para_vetor(NoAVL *raiz, Piloto **vetor, int *indice) {
    if (raiz != NULL) {
        extrair_pilotos_para_vetor(raiz->esquerda, vetor, indice);
        vetor[*indice] = raiz->piloto;
        (*indice)++;
        extrair_pilotos_para_vetor(raiz->direita, vetor, indice);
    }
}

// Função central do módulo que gera o vetor ordenado
static Piloto** gerar_ranking_ordenado(NoAVL *raiz, int *total_pilotos) {
    *total_pilotos = contar_pilotos(raiz);
    if (*total_pilotos == 0) return NULL;

    Piloto **vetor = (Piloto**) malloc((*total_pilotos) * sizeof(Piloto*));
    if (vetor == NULL) return NULL;

    int indice = 0;
    extrair_pilotos_para_vetor(raiz, vetor, &indice);

    // Ordenação (Bubble Sort) por pontuação em ordem decrescente
    for (int i = 0; i < (*total_pilotos) - 1; i++) {
        for (int j = 0; j < (*total_pilotos) - i - 1; j++) {
            if (vetor[j]->pontuacao_campeonato < vetor[j+1]->pontuacao_campeonato) {
                Piloto *temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
    return vetor;
}

// Consultar ranking e Classificação completa
void exibir_ranking_completo(NoAVL *raiz_pilotos) {
    int total;
    Piloto **ranking = gerar_ranking_ordenado(raiz_pilotos, &total);
    
    if (ranking == NULL) {
        printf("Nenhum piloto registrado para o ranking.\n");
        return;
    }

    printf("\n=== RANKING OFICIAL DO CAMPEONATO ===\n");
    for (int i = 0; i < total; i++) {
        printf("%do. %s - %d pontos\n", i + 1, ranking[i]->nome, ranking[i]->pontuacao_campeonato);
    }
    printf("=====================================\n");
    
    free(ranking);
}

// Top 10 pilotos 
void exibir_top_10(NoAVL *raiz_pilotos) {
    int total;
    Piloto **ranking = gerar_ranking_ordenado(raiz_pilotos, &total);
    
    if (ranking == NULL) return;

    int limite = (total < 10) ? total : 10;
    
    printf("\n=== TOP %d PILOTOS ===\n", limite);
    for (int i = 0; i < limite; i++) {
        printf("%do. %s - %d pontos\n", i + 1, ranking[i]->nome, ranking[i]->pontuacao_campeonato);
    }
    
    free(ranking);
}

// Determinar o campeão da temporada e detectar empates 
void determinar_campeao(NoAVL *raiz_pilotos) {
    int total;
    Piloto **ranking = gerar_ranking_ordenado(raiz_pilotos, &total);
    
    if (ranking == NULL || total == 0) return;

    printf("\n*** FIM DA TEMPORADA ***\n");
    
    // Detecção de empate no primeiro lugar
    if (total > 1 && ranking[0]->pontuacao_campeonato == ranking[1]->pontuacao_campeonato) {
        printf("ALERTA: O campeonato terminou em EMPATE!\n");
        printf("Os lideres sao:\n");
        
        int pontuacao_lider = ranking[0]->pontuacao_campeonato;
        for (int i = 0; i < total; i++) {
            if (ranking[i]->pontuacao_campeonato == pontuacao_lider) {
                // Utilizando a Quantidade de Trofeus como critério de desempate técnico
                printf(" - %s (%d pontos, %d trofeus)\n", 
                       ranking[i]->nome, ranking[i]->pontuacao_campeonato, ranking[i]->qtdTrofeus);
            } else {
                break;
            }
        }
        printf("A Federacao deve organizar uma corrida de desempate!\n");
    } else {
        printf("O GRANDE CAMPEAO E: %s com %d pontos!\n", 
               ranking[0]->nome, ranking[0]->pontuacao_campeonato);
    }

    free(ranking);
}