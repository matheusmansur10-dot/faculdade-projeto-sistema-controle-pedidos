#include <ncurses.h> // Para desenhar na tela e ler o teclado
#include <string.h>  // Para copiar textos (strcpy)
#include "pedido.h"  // O "cardápio" deste módulo


// --- Armazenamento de Dados ---
#define MAX_PEDIDOS 100 
static Pedido lista_pedidos[MAX_PEDIDOS];
static int num_pedidos = 0;

// --- Função Auxiliar (Item 28) ---
int analisarPedido(int id) {
    for (int i = 0; i < num_pedidos; i++) {
        if (lista_pedidos[i].id == id) {
            return 1; // Encontrou
        }
    }
    return 0; // Não encontrou
}

// --- Função Principal de Cadastro (Item 29) ---
void inserirPedido() {
    int id_temp, cliente_temp;
    char data_temp[11];

    // 1. Prepara a tela
    clear(); // Limpa a tela do terminal
    box(stdscr, 0, 0); // Desenha uma borda bonita
    mvprintw(1, 2, "=== CADASTRAR NOVO PEDIDO ===");

    // 2. Pede o ID do Pedido
    mvprintw(3, 2, "Digite o ID do Pedido: ");
    echo(); // Habilita aparecer o que você digita
    scanw("%d", &id_temp); // Lê o número digitado

    // 3. Verifica se o ID já existe (Usa sua função do Item 28!)
    if (analisarPedido(id_temp) == 1) {
        attron(A_BOLD); // Negrito
        mvprintw(5, 2, "ERRO: Esse ID ja existe no sistema!");
        attroff(A_BOLD);
        mvprintw(7, 2, "Pressione qualquer tecla para voltar...");
        noecho(); // Desabilita o echo
        getch();  // Espera
        return;   // Cancela e volta para o menu
    }

    // 4. Pede o ID do Cliente
    mvprintw(4, 2, "Digite o ID do Cliente: ");
    scanw("%d", &cliente_temp);

    // 5. Pede a Data
    mvprintw(5, 2, "Data (dd/mm/aaaa): ");
    scanw("%s", data_temp);

    // 6. Salvar os dados no Array (Persistência em Memória)
    if (num_pedidos < MAX_PEDIDOS) {
        lista_pedidos[num_pedidos].id = id_temp;
        lista_pedidos[num_pedidos].clienteId = cliente_temp;
        strcpy(lista_pedidos[num_pedidos].data, data_temp); // Copia a data
        lista_pedidos[num_pedidos].total = 0.0; // Começa com zero
        
        num_pedidos++; // Aumenta o contador de pedidos
        
        mvprintw(7, 2, "Sucesso! Pedido cadastrado.");
    } else {
        mvprintw(7, 2, "Erro: Lista de pedidos cheia!");
    }

    // 7. Finalização
    mvprintw(9, 2, "Pressione qualquer tecla para voltar...");
    noecho(); // Esconde o cursor de novo para o menu ficar bonito
    getch();  // Espera o usuário ler
}
// --- Função de Consulta (Item 30) ---
void consultarPedido() {
    int id_busca;
    int encontrado = 0; // 0 = não achou, 1 = achou

    // 1. Prepara a tela
    clear();
    box(stdscr, 0, 0);
    mvprintw(1, 2, "=== CONSULTAR PEDIDO ===");

    // 2. Pede o ID
    mvprintw(3, 2, "Digite o ID do Pedido para buscar: ");
    echo();
    scanw("%d", &id_busca);
    noecho(); // Desativa o echo logo depois de ler

    // 3. Procura na lista
    for (int i = 0; i < num_pedidos; i++) {
        if (lista_pedidos[i].id == id_busca) {
            // ACHOU! Mostra os dados
            attron(A_BOLD);
            mvprintw(5, 2, "--- PEDIDO ENCONTRADO ---");
            attroff(A_BOLD);
            
            mvprintw(7, 4, "ID do Pedido:  %d", lista_pedidos[i].id);
            mvprintw(8, 4, "ID do Cliente: %d", lista_pedidos[i].clienteId);
            mvprintw(9, 4, "Data:          %s", lista_pedidos[i].data);
            mvprintw(10, 4, "Total:         R$ %.2f", lista_pedidos[i].total);
            
            encontrado = 1; // Marca que achamos
            break; // Para o loop, já achamos o que queríamos
        }
    }

    // 4. Se percorreu tudo e não achou
    if (encontrado == 0) {
        attron(A_BOLD);
        mvprintw(6, 2, "ERRO: Pedido com ID %d nao encontrado!", id_busca);
        attroff(A_BOLD);
    }

    // 5. Finalização
    mvprintw(12, 2, "Pressione qualquer tecla para voltar...");
    getch(); // Espera o usuário ler
}