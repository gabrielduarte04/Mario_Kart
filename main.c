#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Inclusão de todos os TADS do sistema
#include "pilotos.h"
#include "kart.h"
#include "item.h"
#include "corrida.h"
#include "avl_pilotos.h"
#include "heap_corridas.h"
#include "fila_oficina.h"
#include "pilha_itens.h"
#include "lista_historico.h"
#include "campeonato.h"

// Função para iniciar o sistema com dados iniciais 
void inicializar_sistema(NoAVL **arvore, MaxHeap *heap, PilhaItens *pilha_cogumelos, PilhaItens *pilha_cascos, Kart *frota[]) {
    // Cadastrando Pilotos com a função criarPiloto e ordem correta (nome, categoria, status, velBase, qtdTrofeus)
    *arvore = inserir_piloto_no(*arvore, criarPiloto("Mario", "Medio", "Disponivel", 85, 10));
    *arvore = inserir_piloto_no(*arvore, criarPiloto("Bowser", "Pesado", "Disponivel", 95, 8));
    *arvore = inserir_piloto_no(*arvore, criarPiloto("Toad", "Leve", "Disponivel", 70, 5));

    // Cadastrando Corridas 
    inserir_corrida_heap(heap, criar_corrida(1, "Rainbow Road", 3, 99, "Espacial"));
    inserir_corrida_heap(heap, criar_corrida(2, "Luigi Circuit", 3, 20, "Ensolarado"));
    inserir_corrida_heap(heap, criar_corrida(3, "Bowser's Castle", 3, 85, "Lava"));

    // Cadastrando Itens
    adicionar_ao_estoque(pilha_cogumelos, criar_item("Cogumelo Dourado", "Epico", 30));
    adicionar_ao_estoque(pilha_cogumelos, criar_item("Cogumelo Normal", "Comum", 10));
    adicionar_ao_estoque(pilha_cascos, criar_item("Casco Vermelho", "Raro", 20));

    // Cadastrando Karts 
    frota[0] = criar_kart("Standard Kart", "Medio", 70, 70, 70, 100, "Operacional");
    frota[1] = criar_kart("Badwagon", "Pesado", 90, 40, 30, 100, "Operacional");
    frota[2] = criar_kart("Biddybuggy", "Leve", 40, 90, 90, 100, "Operacional");
}

int main() {
    srand(time(NULL));

    NoAVL *arvore_pilotos = NULL;
    MaxHeap *central_corridas = criar_heap(10);
    Oficina *oficina = criar_oficina();
    Historico *historico = criar_historico();
    
    PilhaItens *pilha_cogumelos = criar_pilha();
    PilhaItens *pilha_cascos = criar_pilha();
    Kart *frota_karts[10]; // Frota global disponível

    // Carrega os dados iniciais na memória
    inicializar_sistema(&arvore_pilotos, central_corridas, pilha_cogumelos, pilha_cascos, frota_karts);

    char opcao = '0';

    
    // LOOP DO MENU PRINCIPAL
    while (opcao != '8') {
        printf("\n=======================================\n");
        printf("      CENTRAL DO GRANDE PREMIO DO REINO COGUMELO      \n");
        printf("=======================================\n");
        printf("1. Pilotos (Top 10)\n");
        printf("2. Oficina E. Gadd\n");
        printf("3. Proximas Corridas\n");
        printf("4. Historico de Corridas\n");
        printf("5. Encerrar Temporada (Ver Campeao)\n");
        printf("6. [!] INICIAR PROXIMA CORRIDA [!]\n");
        printf("7. Sair e Desligar Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%c", &opcao);

        switch (opcao) {
            case '1':
                exibir_top_10(arvore_pilotos);
                break;
            case '2':
                consultar_fila(oficina);
                // Exemplo de como a oficina opera: conserta o primeiro da fila
                printf("\nDeseja iniciar um reparo? (1-Sim / 0-Nao): ");
                int rep; scanf("%d", &rep);
                if (rep == 1) iniciar_reparo(oficina);
                break;
            case '3':
                visualizar_proximas_corridas(central_corridas);
                break;
            case '4':
                navegar_historico(historico);
                break;
            case '5':
                determinar_campeao(arvore_pilotos);
                break;
            case '6': {
                // ---------------------------------------------------------
                // 3. A INTEGRAÇÃO GLOBAL: FASE DE PREPARAÇÃO E SIMULAÇÃO
                // ---------------------------------------------------------
                
                // A. Puxa a corrida mais perigosa do Max-Heap
                Corrida *corrida_atual = extrair_proxima_corrida(central_corridas);
                
                if (corrida_atual == NULL) {
                    printf("\nNenhuma corrida agendada na central!\n");
                    break;
                }

                // B. Escala os participantes (Buscando na Árvore AVL)
                Participante grid[3];
                grid[0].piloto = buscar_piloto_por_nome(arvore_pilotos, "Mario");
                grid[1].piloto = buscar_piloto_por_nome(arvore_pilotos, "Bowser");
                grid[2].piloto = buscar_piloto_por_nome(arvore_pilotos, "Toad");

                // C. Atribui os Karts
                grid[0].kart = frota_karts[0];
                grid[1].kart = frota_karts[1];
                grid[2].kart = frota_karts[2];

                // D. Distribui os Itens (Retirando das Pilhas)
                grid[0].item = distribuir_item(pilha_cogumelos);
                grid[1].item = distribuir_item(pilha_cascos);
                grid[2].item = NULL; // Toad corre sem item nesta simulação

                // E. Roda a Matemática da Corrida
                simular_corrida(corrida_atual, grid, 3);

                // F. Consequências da Corrida
                atualizar_pontuacoes(grid, 3); // Atualiza o ranking do campeonato
                registrar_corrida_historico(historico, corrida_atual, grid, 3); // Salva na Lista Dupla

                // G. Envia os karts quebrados para as Filas da Oficina
                for (int i = 0; i < 3; i++) {
                    if (strcmp(grid[i].kart->status, "Danificado") == 0 || 
                        strcmp(grid[i].kart->status, "Destruido") == 0) {
                        registrar_kart_manutencao(oficina, grid[i].kart);
                    }
                    
                    // Consome o item definitivamente (libera a memória)
                    if (grid[i].item != NULL) {
                        consumir_item_definitivamente(grid[i].item);
                        grid[i].item = NULL;
                    }
                }

                // Libera a memória da corrida finalizada
                liberar_corrida(corrida_atual);
                break;
            }
            case '7': {
                char nome[50], categoria[20];
                int velocidade;

                printf("\n--- NOVO CADASTRO DE PILOTO ---\n");
                printf("Nome do piloto: ");
                scanf(" %49[^\n]", nome); // Lê a string com espaços, limitando a 49 caracteres

                printf("Categoria (Leve, Medio, Pesado): ");
                scanf(" %19s", categoria); // Lê a próxima palavra

                printf("Velocidade Base (0 a 100): ");
                scanf("%d", &velocidade);

                // Instancia e insere o piloto na Árvore AVL. 
                // Troféus (0) e Status ("Disponivel") são passados por padrão.
                Piloto *novo_piloto = criar_piloto(nome, categoria, velocidade, 0, "Disponivel");
                arvore_pilotos = inserir_piloto_no(arvore_pilotos, novo_piloto);
                
                printf("Sucesso! %s foi registrado na Federacao.\n", nome);
                break;
            }
            case '8':
                printf("Desligando sistemas da Federacao...\n");
                // LIBERAÇÃO DE MEMÓRIA 
                liberar_arvore(arvore_pilotos);
                liberar_heap(central_corridas);
                liberar_oficina(oficina);
                liberar_historico(historico);
                liberar_pilha(pilha_cogumelos);
                liberar_pilha(pilha_cascos);
                
                for (int i = 0; i < 3; i++) {
                    liberar_kart(frota_karts[i]);
                }
                break;
            default:
                printf("Opcao invalida, Senhor.\n");
        }
    }

    return 0;
}