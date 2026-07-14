#ifndef KART_H
#define KART_H

typedef struct {
    char nome[50];
    char tipo[30];
    int velocidade;
    int aceleracao;
    int controle;
    int durabilidade;
    char status[20];
} Kart;

Kart* criar_kart(const char *nome, const char *tipo, int vel, int ace, int con, int dur, const char *status);
void imprimir_kart(Kart *k);
void liberar_kart(Kart *k);

#endif