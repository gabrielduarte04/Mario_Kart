#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_oficina.h"

Oficina* criar_oficina() {
    Oficina *of = (Oficina*) malloc(sizeof(Oficina));
    if (of != NULL) {
        of->frente_destruidos = NULL;
        of->tras_destruidos = NULL;
        of->frente_danificados = NULL;
        of->tras_danificados = NULL;
    }
    return of;
}

// Função privada para adicionar na fila especificada
static void enfileirar(NoFila **frente, NoFila **tras, Kart *k) {
    NoFila *novo = (NoFila*) malloc(sizeof(NoFila));
    if (novo != NULL) {
        novo->kart = k;
        novo->prox = NULL;
        
        if (*tras == NULL) { // Fila vazia
            *frente = novo;
            *tras = novo;
        } else {
            (*tras)->prox = novo;
            *tras = novo;
        }
    }
}

// Registrar karts para manutenção
void registrar_kart_manutencao(Oficina *oficina, Kart *k) {
    if (oficina == NULL || k == NULL) return;
    
    if (strncmp(k->status, "Destruido", 9) == 0) {
        enfileirar(&(oficina->frente_destruidos), &(oficina->tras_destruidos), k);
        printf("Aviso: Kart %s entrou na fila de PRIORIDADE MAXIMA.\n", k->nome);
    } else if (strncmp(k->status, "Danificado", 10) == 0) {
        enfileirar(&(oficina->frente_danificados), &(oficina->tras_danificados), k);
        printf("Aviso: Kart %s entrou na fila de espera normal.\n", k->nome);
    }
}

//Iniciar reparos e Liberar karts reparados
Kart* iniciar_reparo(Oficina *oficina) {
    if (oficina == NULL) return NULL;
    
    NoFila *removido = NULL;
    NoFila **frente_alvo = NULL;
    NoFila **tras_alvo = NULL;

    //A lógica de prioridade: sempre os Destruídos primeiro 
    if (oficina->frente_destruidos != NULL) {
        frente_alvo = &(oficina->frente_destruidos);
        tras_alvo = &(oficina->tras_destruidos);
    } else if (oficina->frente_danificados != NULL) {
        frente_alvo = &(oficina->frente_danificados);
        tras_alvo = &(oficina->tras_danificados);
    } else {
        printf("Oficina vazia. Nenhum reparo pendente.\n");
        return NULL;
    }

    // Retira o primeiro da fila
    removido = *frente_alvo;
    *frente_alvo = removido->prox;
    if (*frente_alvo == NULL) { // Se a fila esvaziou
        *tras_alvo = NULL;
    }

    Kart *k = removido->kart;
    free(removido);

    // Após o reparo retornam ao estado Operacional 
    strncpy(k->status, "Operacional", sizeof(k->status) - 1);
    k->status[sizeof(k->status) - 1] = '\0';
    
    printf("Sucesso! Kart %s foi reparado e esta Operacional.\n", k->nome);
    return k;
}

//Consultar fila de manutenção
static void imprimir_fila(NoFila *frente) {
    NoFila *atual = frente;
    int pos = 1;
    while (atual != NULL) {
        printf("  %d. %s\n", pos++, atual->kart->nome);
        atual = atual->prox;
    }
}

void consultar_fila(Oficina *oficina) {
    if (oficina == NULL) return;
    
    printf("\n=== STATUS DA OFICINA ===\n");
    printf("Prioridade 1 (Destruidos):\n");
    if (oficina->frente_destruidos == NULL) printf("  [Vazia]\n");
    else imprimir_fila(oficina->frente_destruidos);
    
    printf("Prioridade 2 (Danificados):\n");
    if (oficina->frente_danificados == NULL) printf("  [Vazia]\n");
    else imprimir_fila(oficina->frente_danificados);
    printf("=========================\n");
}

// Liberação de memória
static void esvaziar_fila(NoFila **frente, NoFila **tras) {
    NoFila *atual = *frente;
    while (atual != NULL) {
        NoFila *temp = atual;
        atual = atual->prox; 
        // Não da free(temp->kart) porque o veículo voltará a ser usado no sistema.
        free(temp);
    }
    *frente = NULL;
    *tras = NULL;
}

void liberar_oficina(Oficina *oficina) {
    if (oficina != NULL) {
        esvaziar_fila(&(oficina->frente_destruidos), &(oficina->tras_destruidos));
        esvaziar_fila(&(oficina->frente_danificados), &(oficina->tras_danificados));
        free(oficina);
    }
}