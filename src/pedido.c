#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h> // Interface
#include "pedido.h"
#include "cliente.h" // Para validar se cliente existe
#include "produto.h" // Para pegar preço do produto
#include "persistencia.h" 

// CRIAÇÃO DAS VARIÁVEIS GLOBAIS
Pedido lista_pedidos[MAX_PEDIDOS];
int num_pedidos = 0;

// Funções auxiliares simples
int clienteExiste(int id) {
    for(int i=0; i<totalPF; i++) if(listaPF[i].base.id == id) return 1;
    for(int i=0; i<totalPJ; i++) if(listaPJ[i].base.id == id) return 1;
    return 0;
}

double getPrecoProduto(int id) {
    for(int i=0; i<qtd_produtos; i++) {
        if(lista_produtos[i].id == id) return lista_produtos[i].preco;
    }
    return 0.0;
}

void inserirPedido() {
    if (num_pedidos >= MAX_PEDIDOS) {
        clear(); mvprintw(2, 2, "Erro: Memoria cheia!"); getch(); return;
    }

    Pedido p;
    p.total = 0.0;
    p.qtdProdutos = 0;

    echo(); curs_set(1);
    clear(); box(stdscr, 0, 0);
    mvprintw(1, 2, "=== NOVO PEDIDO ===");

    mvprintw(3, 2, "ID do Pedido: ");
    scanw("%d", &p.id);

    // Validação Cliente
    while(1) {
        mvprintw(4, 2, "ID do Cliente:      "); move(4, 17);
        scanw("%d", &p.clienteId);
        if(clienteExiste(p.clienteId)) {
            mvprintw(4, 30, "[OK]"); break;
        }
        mvprintw(4, 30, "[Erro: Cliente nao existe]");
    }

    mvprintw(5, 2, "Data (dd/mm/aaaa): ");
    scanw("%s", p.data);

    // Adicionar Produtos
    mvprintw(7, 2, "--- Adicionar Produtos (ID 0 para parar) ---");
    int linha = 8;
    while(p.qtdProdutos < 10) {
        int prodId;
        mvprintw(linha, 2, "Produto %d ID: ", p.qtdProdutos+1);
        scanw("%d", &prodId);

        if(prodId == 0) break;

        double preco = getPrecoProduto(prodId);
        if(preco > 0) {
            p.produtosIds[p.qtdProdutos] = prodId;
            p.total += preco;
            p.qtdProdutos++;
            mvprintw(linha, 25, "R$ %.2f [Add]", preco);
            linha++;
        } else {
            mvprintw(linha, 25, "[Nao encontrado]");
        }
    }

    // Grava na memória RAM
    lista_pedidos[num_pedidos] = p;
    num_pedidos++;

    // --- AQUI QUE SALVA NO ARQUIVO ---
    salvarPedidos(); 
    // ---------------------------------

    noecho(); curs_set(0);
    attron(A_BOLD);
    mvprintw(linha+2, 2, "Total: R$ %.2f", p.total);
    mvprintw(linha+4, 2, ">>> Pedido Salvo com Sucesso! <<<");
    attroff(A_BOLD);
    getch();
}

void consultarPedido() {
    int id;
    echo(); curs_set(1); clear(); box(stdscr, 0, 0);
    mvprintw(1, 2, "=== CONSULTAR PEDIDO ===");
    mvprintw(3, 2, "ID: "); scanw("%d", &id); noecho(); curs_set(0);

    for(int i=0; i<num_pedidos; i++) {
        if(lista_pedidos[i].id == id) {
            mvprintw(5, 2, "Pedido #%d | Cli: %d", lista_pedidos[i].id, lista_pedidos[i].clienteId);
            mvprintw(6, 2, "Data: %s", lista_pedidos[i].data);
            mvprintw(7, 2, "Itens: %d", lista_pedidos[i].qtdProdutos);
            mvprintw(8, 2, "TOTAL: R$ %.2f", lista_pedidos[i].total);
            getch(); return;
        }
    }
    mvprintw(5, 2, "Nao encontrado."); getch();
}

void listarPedidos() {
    clear(); box(stdscr, 0, 0);
    mvprintw(1, 2, "=== LISTA DE PEDIDOS ===");
    for(int i=0; i<num_pedidos; i++) {
        mvprintw(3+i, 2, "ID: %d | Cli: %d | R$ %.2f", 
            lista_pedidos[i].id, lista_pedidos[i].clienteId, lista_pedidos[i].total);
    }
    mvprintw(LINES-2, 2, "Total: %d pedidos. Enter para voltar.", num_pedidos);
    getch();
}

void removerPedido() {
    int id;
    echo(); curs_set(1); clear(); box(stdscr, 0, 0);
    mvprintw(1, 2, "=== REMOVER PEDIDO ===");
    mvprintw(3, 2, "ID: "); scanw("%d", &id); noecho(); curs_set(0);

    for(int i=0; i<num_pedidos; i++) {
        if(lista_pedidos[i].id == id) {
            for(int j=i; j<num_pedidos-1; j++) lista_pedidos[j] = lista_pedidos[j+1];
            num_pedidos--;
            salvarPedidos(); // Atualiza arquivo
            mvprintw(5, 2, "Removido!");
            getch(); return;
        }
    }
    mvprintw(5, 2, "Nao encontrado."); getch();
}