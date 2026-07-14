#ifndef PILOTOS_H
#define PILOTOS_H

typedef struct {
    char nome[50];
    char categoria[20];
    char status[20];
    int velBase;
    int qtdTrofeus;
    int pontuacao_campeonato;
}Piloto;

Piloto* criarPiloto(const char *nome, const char *categoria, char *status, int velBase, int qtdTrofeus );

void imprimirPiloto(Piloto *p);
void liberarPiloto(Piloto *p);

#endif