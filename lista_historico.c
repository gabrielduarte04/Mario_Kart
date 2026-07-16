#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_historico.h"

// Estrutura auxiliar para a tabela de contagem temporária
typedef struct {
    char nome[50];
    int contagem;
} ContadorPiloto;

Historico* criar_historico() {
    Historico *h = (Historico*) malloc(sizeof(Historico));
    if (h != NULL) {
        h->inicio = NULL;
        h->fim = NULL;
    }
    return h;
}

// Registrar corridas concluídas 
void registrar_corrida_historico(Historico *h, Corrida *c, Participante partes[], int qtd) {
    if (h == NULL || c == NULL || partes == NULL) return;

    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL) return;

    // Preenche o registro com os dados da corrida finalizada
    strncpy(novo->dados.nome_pista, c->nome_pista, 49);
    novo->dados.nome_pista[49] = '\0';
    
    // O vencedor é sempre o primeiro do array após a ordenação na fase de simulação
    strncpy(novo->dados.vencedor, partes[0].piloto->nome, 49);
    novo->dados.vencedor[49] = '\0';

    novo->dados.qtd_participantes = qtd;
    novo->dados.total_acidentes = 0;

    for (int i = 0; i < qtd; i++) {
        strncpy(novo->dados.participantes[i], partes[i].piloto->nome, 49);
        novo->dados.participantes[i][49] = '\0';
        
        // Verifica se houve acidentes ou destruição total para o contador
        if (strcmp(partes[i].kart->status, "Danificado") == 0 || 
            strcmp(partes[i].kart->status, "Destruido") == 0) {
            novo->dados.total_acidentes++;
        }
    }

    // Configuração dos ponteiros da lista dupla (inserção no fim)
    novo->proximo = NULL;
    novo->anterior = h->fim;

    if (h->inicio == NULL) {
        h->inicio = novo;
    } else {
        h->fim->proximo = novo;
    }
    h->fim = novo;
}

//Navegar pelo histórico
void navegar_historico(Historico *h) {
    if (h == NULL || h->inicio == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    Nodo *atual = h->inicio;
    char comando = 'n';

    while (atual != NULL && comando != 's') {
        printf("\n--- REGISTRO DE CORRIDA ---\n");
        printf("Pista: %s | Vencedor: %s | Acidentes: %d\n", 
               atual->dados.nome_pista, atual->dados.vencedor, atual->dados.total_acidentes);
        
        printf("[p] Proxima  |  [a] Anterior  |  [s] Sair da navegacao: ");
        scanf(" %c", &comando);

        if (comando == 'p' && atual->proximo != NULL) {
            atual = atual->proximo;
        } else if (comando == 'a' && atual->anterior != NULL) {
            atual = atual->anterior;
        } else if (comando != 's') {
            printf("Limite do historico atingido ou comando invalido.\n");
        }
    }
}

// Ranking histórico de vitórias
void exibir_ranking_vitorias(Historico *h) {
    if (h == NULL || h->inicio == NULL) return;
    
    printf("\n--- ULTIMOS VENCEDORES ---\n");
    Nodo *atual = h->inicio;
    while (atual != NULL) {
        printf(" -> %s (Pista: %s)\n", atual->dados.vencedor, atual->dados.nome_pista);
        atual = atual->proximo;
    }

}

//Pistas com maior número de acidentes
void exibir_pistas_com_mais_acidentes(Historico *h) {
    if (h == NULL || h->inicio == NULL) return;

    Nodo *atual = h->inicio;
    Nodo *pista_perigosa = atual;

    while (atual != NULL) {
        if (atual->dados.total_acidentes > pista_perigosa->dados.total_acidentes) {
            pista_perigosa = atual;
        }
        atual = atual->proximo;
    }

    printf("\n--- PISTA MAIS PERIGOSA DO HISTORICO ---\n");
    printf("Pista: %s com %d acidentes registrados em uma unica corrida.\n", pista_perigosa->dados.nome_pista, pista_perigosa->dados.total_acidentes);
}

// Pilotos com maior número de participações
void exibir_piloto_com_mais_participacoes(Historico *h) {
    if (h == NULL || h->inicio == NULL) {
        printf("\nHistorico vazio. Nenhuma corrida registada ainda.\n");
        return;
    }

    ContadorPiloto tabela[100];
    int qtd_unicos = 0;

    for (int i = 0; i < 100; i++) {
        tabela[i].contagem = 0;
        tabela[i].nome[0] = '\0';
    }

    Nodo *atual = h->inicio;

    while (atual != NULL) {
        for (int i = 0; i < atual->dados.qtd_participantes; i++) {
            const char *nome_piloto = atual->dados.participantes[i];
            int encontrado = 0;

            for (int j = 0; j < qtd_unicos; j++) {
                if (strcmp(tabela[j].nome, nome_piloto) == 0) {
                    tabela[j].contagem++;
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado && qtd_unicos < 100) {
                strncpy(tabela[qtd_unicos].nome, nome_piloto, sizeof(tabela[qtd_unicos].nome) - 1);
                tabela[qtd_unicos].nome[sizeof(tabela[qtd_unicos].nome) - 1] = '\0';
                tabela[qtd_unicos].contagem = 1;
                qtd_unicos++;
            }
        }
        atual = atual->proximo;
    }

    if (qtd_unicos == 0) {
        printf("\nNenhum piloto encontrado no historico.\n");
        return;
    }

    int max_participacoes = -1;
    char nome_lider[50] = "";

    for (int i = 0; i < qtd_unicos; i++) {
        if (tabela[i].contagem > max_participacoes) {
            max_participacoes = tabela[i].contagem;
            strcpy(nome_lider, tabela[i].nome);
        }
    }

    printf("\n============================================\n");
    printf("  PILOTO COM MAIS PARTICIPACOES NA TEMPORADA  \n");
    printf("============================================\n");
    printf("Piloto: %s\n", nome_lider);
    printf("Total de Corridas Disputadas: %d\n", max_participacoes);
    printf("============================================\n");
}

void liberar_historico(Historico *h) {
    if (h != NULL) {
        Nodo *atual = h->inicio;
        while (atual != NULL) {
            Nodo *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        free(h);
    }
}