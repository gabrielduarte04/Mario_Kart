#ifndef ITEM_H
#define ITEM_H

typedef struct {
    char nome[50];
    char raridade[20];
    int poder;
} Item;

Item* criar_item(const char *nome, const char *raridade, int poder);
void imprimir_item(Item *i);
void liberar_item(Item *i);

#endif