# Sistema de Gerenciamento: Grande Prêmio Mushroom Kart Racing

Este projeto consiste na implementação da Central Digital do Grande Prêmio para a Federação Mushroom Kart Racing, desenvolvido como trabalho final da disciplina de Algoritmos e Estruturas de Dados I. O sistema utiliza estruturas de dados para otimizar o gerenciamento de pilotos, corridas, itens, oficina e pontuação da temporada.

## Estruturas de Dados Implementadas
O projeto utiliza cinco estruturas principais para garantir a eficiência e o gerenciamento de memória:
* **Árvore AVL**: Armazenamento e busca rápida de pilotos.
* **Max-Heap**: Gerenciamento de prioridade na central de corridas.
* **Filas**: Organização da oficina (priorizando karts destruídos/danificados).
* **Lista Duplamente Encadeada**: Armazenamento do histórico de corridas finalizadas.
* **Pilhas**: Gestão do estoque de itens da Federação.

## Como Compilar e Executar

### Pré-requisitos
* Compilador GCC instalado no sistema.

### Via Terminal (Recomendado)
Para compilar o projeto utilizando o compilador GCC diretamente:

1. Abra o terminal na pasta raiz do projeto.
2. Execute o comando de compilação:
   ```
   gcc -Wall -Wextra -std=c99 -g *.c -o central_gp
   ```
3. Execute o programa:
   * **Windows**: `.\central_gp.exe`
   * **Linux/WSL**: `./central_gp`

### Via Makefile
Se o utilitário `make` estiver disponível no seu ambiente, basta executar:
```
make
```
Para limpar os arquivos gerados após o uso:
```
make clean
```

## Informações do Desenvolvedor
* **Aluno**: Gabriel Barbosa Duarte
* **Disciplina**: Algoritmos e Estruturas de Dados I
* **Turma**: M1