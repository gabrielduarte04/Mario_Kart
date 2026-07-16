#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_pilotos.h"

// Funções auxiliares privadas da AVL
static int obter_altura(NoAVL *n) {
    if (n == NULL) return 0;
    return n->altura;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static NoAVL* criar_no(Piloto *p) {
    NoAVL *no = (NoAVL*) malloc(sizeof(NoAVL));
    if (no != NULL) {
        no->piloto = p;
        no->esquerda = NULL;
        no->direita = NULL;
        no->altura = 1; 
    }
    return no;
}

static int obter_fator_balanceamento(NoAVL *n) {
    if (n == NULL) return 0;
    return obter_altura(n->esquerda) - obter_altura(n->direita);
}

static NoAVL* rotacionar_direita(NoAVL *y) {
    NoAVL *x = y->esquerda;
    NoAVL *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(obter_altura(y->esquerda), obter_altura(y->direita)) + 1;
    x->altura = max(obter_altura(x->esquerda), obter_altura(x->direita)) + 1;

    return x;
}

static NoAVL* rotacionar_esquerda(NoAVL *x) {
    NoAVL *y = x->direita;
    NoAVL *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(obter_altura(x->esquerda), obter_altura(x->direita)) + 1;
    y->altura = max(obter_altura(y->esquerda), obter_altura(y->direita)) + 1;

    return y;
}

static NoAVL* no_com_valor_minimo(NoAVL *no) {
    NoAVL *atual = no;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Inserção 
NoAVL* inserir_piloto_no(NoAVL *no, Piloto *p) {
    if (no == NULL) return criar_no(p);

    int comp = strcmp(p->nome, no->piloto->nome);

    if (comp < 0) {
        no->esquerda = inserir_piloto_no(no->esquerda, p);
    } else if (comp > 0) {
        no->direita = inserir_piloto_no(no->direita, p);
    } else {
        return no; // Nomes duplicados não são inseridos
    }

    no->altura = 1 + max(obter_altura(no->esquerda), obter_altura(no->direita));
    int balanceamento = obter_fator_balanceamento(no);

    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && strcmp(p->nome, no->esquerda->piloto->nome) < 0) {
        return rotacionar_direita(no);
    }
    // Caso Direita-Direita
    if (balanceamento < -1 && strcmp(p->nome, no->direita->piloto->nome) > 0) {
        return rotacionar_esquerda(no);
    }
    // Caso Esquerda-Direita
    if (balanceamento > 1 && strcmp(p->nome, no->esquerda->piloto->nome) > 0) {
        no->esquerda = rotacionar_esquerda(no->esquerda);
        return rotacionar_direita(no);
    }
    // Caso Direita-Esquerda
    if (balanceamento < -1 && strcmp(p->nome, no->direita->piloto->nome) < 0) {
        no->direita = rotacionar_direita(no->direita);
        return rotacionar_esquerda(no);
    }

    return no;
}

// Remoção 
NoAVL* remover_piloto_no(NoAVL *raiz, const char *nome) {
    if (raiz == NULL) return raiz;

    int comp = strcmp(nome, raiz->piloto->nome);

    if (comp < 0) {
        raiz->esquerda = remover_piloto_no(raiz->esquerda, nome);
    } else if (comp > 0) {
        raiz->direita = remover_piloto_no(raiz->direita, nome);
    } else {
        // Encontrou o nó a ser removido
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
            NoAVL *temp;
            if (raiz->esquerda != NULL) {
                temp = raiz->esquerda;
            } else {
                temp = raiz->direita;
            }

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp; // Copia o conteúdo do filho não-nulo
            }
            liberar_piloto(temp->piloto);
            free(temp);
        } else {
            NoAVL *temp = no_com_valor_minimo(raiz->direita);
            
            // Substitui o piloto atual pelo sucessor em ordem
            liberar_piloto(raiz->piloto);
            raiz->piloto = criar_piloto(temp->piloto->nome, temp->piloto->categoria, temp->piloto->status, temp->piloto->velBase, temp->piloto->qtdTrofeus);

            raiz->direita = remover_piloto_no(raiz->direita, temp->piloto->nome);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = 1 + max(obter_altura(raiz->esquerda), obter_altura(raiz->direita));
    int balanceamento = obter_fator_balanceamento(raiz);

    if (balanceamento > 1 && obter_fator_balanceamento(raiz->esquerda) >= 0) {
        return rotacionar_direita(raiz);
    }
    if (balanceamento > 1 && obter_fator_balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacionar_esquerda(raiz->esquerda);
        return rotacionar_direita(raiz);
    }
    if (balanceamento < -1 && obter_fator_balanceamento(raiz->direita) <= 0) {
        return rotacionar_esquerda(raiz);
    }
    if (balanceamento < -1 && obter_fator_balanceamento(raiz->direita) > 0) {
        raiz->direita = rotacionar_direita(raiz->direita);
        return rotacionar_esquerda(raiz);
    }

    return raiz;
}

// Consulta por nome
Piloto* buscar_piloto_por_nome(NoAVL *raiz, const char *nome) {
    if (raiz == NULL) return NULL;

    int comp = strcmp(nome, raiz->piloto->nome);

    if (comp == 0) return raiz->piloto;
    if (comp < 0) return buscar_piloto_por_nome(raiz->esquerda, nome);
    return buscar_piloto_por_nome(raiz->direita, nome);
}

// Listar pilotos suspensos 
void listar_pilotos_suspensos(NoAVL *raiz) {
    if (raiz != NULL) {
        listar_pilotos_suspensos(raiz->esquerda);
        if (strcmp(raiz->piloto->status, "Suspenso") == 0) {
            imprimir_piloto(raiz->piloto);
        }
        listar_pilotos_suspensos(raiz->direita);
    }
}

// Listar pilotos por categoria
void listar_pilotos_por_categoria(NoAVL *raiz, const char *categoria) {
    if (raiz != NULL) {
        listar_pilotos_por_categoria(raiz->esquerda, categoria);
        if (strcmp(raiz->piloto->categoria, categoria) == 0) {
            imprimir_piloto(raiz->piloto);
        }
        listar_pilotos_por_categoria(raiz->direita, categoria);
    }
}

// Busca o piloto com maior número de troféus
void encontrar_maior_trofeus(NoAVL *raiz, Piloto **melhor) {
    if (raiz != NULL) {
        encontrar_maior_trofeus(raiz->esquerda, melhor);
        if (*melhor == NULL || raiz->piloto->qtdTrofeus > (*melhor)->qtdTrofeus) {
            *melhor = raiz->piloto;
        }
        encontrar_maior_trofeus(raiz->direita, melhor);
    }
}

// Desalocação completa da memória da árvore
void liberar_arvore(NoAVL *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);
        liberar_arvore(raiz->direita);
        liberar_piloto(raiz->piloto);
        free(raiz);
    }
}