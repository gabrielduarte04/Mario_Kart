makefile_content = """
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = central_gp

SRCS = main.c avl_pilotos.c campeonato.c corrida.c fila_oficina.c heap_corridas.c item.c kart.c lista_historico.c pilha_itens.c pilotos.c
OBJS = $(SRCS:.c=.o)
HEADERS = avl_pilotos.h campeonato.h corrida.h fila_oficina.h heap_corridas.h item.h kart.h lista_historico.h pilha_itens.h pilotos.h

all: $(TARGET)

$(TARGET): $(OBJS)
\t$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HEADERS)
\t$(CC) $(CFLAGS) -c $< -o $@

clean:
\trm -f $(OBJS) $(TARGET) central_gp.exe

.PHONY: all clean
"""

with open("Makefile", "w", encoding="utf-8") as f:
    f.write(makefile_content)