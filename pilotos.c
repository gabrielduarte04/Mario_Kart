#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilotos.h"

//criando um piloto
Piloto* criarPiloto(const char *nome, const char *categoria, char *status, int velBase, int qtdTrofeus){
    Piloto* p = (Piloto*) malloc(sizeof(Piloto));

    if(p != NULL){
        strncpy(p->nome, nome, sizeof(p->nome) - 1);
        p->nome[sizeof(p->nome) - 1] = '\0';

        strncpy(p->categoria , categoria, sizeof(p->categoria) - 1);
        p->categoria[sizeof(p->categoria) - 1] = '\0';

        strncpy(p->status, status, sizeof(p->status) - 1);
        p->status[sizeof(p->status) - 1] = '\0';

        p->velBase = velBase;
        p->qtdTrofeus = qtdTrofeus;
        p->pontuacao_campeonato = 0;
    }

    return p;
}

//imprimindo informações de um piloto especifico
void imprimirPiloto(Piloto *p){
    printf("Piloto: %s/nCategoria: %s/nStatus: %s/nVelocidade Base: %d\nQuantidade de Troféus: %d", p->nome, p->categoria, p->status, p->velBase, p->qtdTrofeus);
}

//libera memoria de um piloto especifico
void liberarPiloto(Piloto *p){
    if(p != NULL){
        free(p);
    }
}