#ifndef AVL_PILOTOS_H
#define AVL_PILOTOS_H

#include "pilotos.h"

// Estrutura do nó da Árvore AVL
typedef struct NoAVL {
    Piloto *piloto;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
    int altura;
} NoAVL;

// Funções principais da árvore
NoAVL* inserir_piloto_no(NoAVL *raiz, Piloto *p);
NoAVL* remover_piloto_no(NoAVL *raiz, const char *nome);
Piloto* buscar_piloto_por_nome(NoAVL *raiz, const char *nome);

void listar_pilotos_suspensos(NoAVL *raiz);
void listar_pilotos_por_categoria(NoAVL *raiz, const char *categoria);
void encontrar_maior_trofeus(NoAVL *raiz, Piloto **melhor);

// Função para liberação de memória
void liberar_arvore(NoAVL *raiz);

#endif