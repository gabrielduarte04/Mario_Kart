#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kart.h"

Kart* criar_kart(const char *nome, const char *tipo, int vel, int ace, int con, int dur, const char *status) {
    Kart *k = (Kart*) malloc(sizeof(Kart));
    
    if (k != NULL) {
        strncpy(k->nome, nome, sizeof(k->nome) - 1);
        k->nome[sizeof(k->nome) - 1] = '\0';
        
        strncpy(k->tipo, tipo, sizeof(k->tipo) - 1);
        k->tipo[sizeof(k->tipo) - 1] = '\0';
        
        strncpy(k->status, status, sizeof(k->status) - 1);
        k->status[sizeof(k->status) - 1] = '\0';
        
        k->velocidade = vel;
        k->aceleracao = ace;
        k->controle = con;
        k->durabilidade = dur;
    }
    
    return k;
}

void imprimir_kart(Kart *k) {
    if (k != NULL) {
        printf("Kart: %s | Tipo: %s | Vel: %d | Ace: %d | Con: %d | Dur: %d | Status: %s\n",
               k->nome, k->tipo, k->velocidade, k->aceleracao, k->controle, k->durabilidade, k->status);
    }
}

void liberar_kart(Kart *k) {
    if (k != NULL) {
        free(k);
    }
}