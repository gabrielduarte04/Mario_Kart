#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

Item* criar_item(const char *nome, const char *raridade, int poder) {
    Item *i = (Item*) malloc(sizeof(Item));
    
    if (i != NULL) {
        strncpy(i->nome, nome, sizeof(i->nome) - 1);
        i->nome[sizeof(i->nome) - 1] = '\0';
        
        strncpy(i->raridade, raridade, sizeof(i->raridade) - 1);
        i->raridade[sizeof(i->raridade) - 1] = '\0';
        
        i->poder = poder;
    }
    
    return i;
}

void imprimir_item(Item *i) {
    if (i != NULL) {
        printf("Item: %s | Raridade: %s | Poder: %d\n", i->nome, i->raridade, i->poder);
    }
}

void liberar_item(Item *i) {
    if (i != NULL) {
        free(i);
    }
}