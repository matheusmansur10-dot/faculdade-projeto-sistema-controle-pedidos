#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "cliente.h"
#include "produto.h"
#include "pedido.h"

// --- PROTÓTIPOS (Para o compilador não se perder) ---
void mostrarMenuCliente();
void mostrarMenuProdutos();
void mostrarMenuPedidos();

// --- FUNÇÕES AUXILIARES DE DESENHO ---

void desenha_menu_generico(WINDOW *win, char *titulo, char *opcoes[], int n_opcoes, int destaque) {
    box(win, 0, 0);
    // Centraliza o título
    int largura = getmaxx(win);
    mvwprintw(win, 1, (largura - strlen(titulo)) / 2, "%s", titulo);

    for (int i = 0; i < n_opcoes; i++) {
        if (i == destaque) {
            wattron(win, A_REVERSE);
            mvwprintw(win, i + 3, 2, " > %s", opcoes[i]);
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, i + 3, 2, "   %s", opcoes[i]);
        }
    }
    mvwprintw(win, getmaxy(win) - 2, 2, "Use as setas e Enter");
    wrefresh(win);
}

// --- MENU DE CLIENTES ---

void mostrarMenuCliente() {
    char *opcoes[] = {
        "1. Cadastrar Cliente",
        "2. Consultar Cliente",
        "3. Remover Cliente",
        "4. Listar Clientes",
        "5. Voltar"
    };
    int n_opcoes = 5;

    int altura = 12, largura = 45;
    int inicio_y = (LINES - altura) / 2;
    int inicio_x = (COLS - largura) / 2;

    WINDOW *win = newwin(altura, largura, inicio_y, inicio_x);
    keypad(win, TRUE);

    int destaque = 0;
    int ch;

    while(1) {
        desenha_menu_generico(win, "MODULO DE CLIENTES", opcoes, n_opcoes, destaque);
        ch = wgetch(win);

        switch(ch) {
            case KEY_UP:
                if (destaque > 0) destaque--;
                break;
            case KEY_DOWN:
                if (destaque < n_opcoes - 1) destaque++;
                break;
            case 10: // Enter
                if (destaque == 4) { // Voltar
                    delwin(win);
                    return; 
                }
                
                // Ações
                if (destaque == 0) cadastrarCliente();
                if (destaque == 1) consultarCliente();
                if (destaque == 2) removerCliente();
                if (destaque == 3) listarClientes();

                // Restaura a tela após a ação
                clear();
                refresh();
                box(win, 0, 0); // Redesenha borda se precisar
                keypad(win, TRUE); // Reativa setas!
                break;
        }
    }
}

// --- MENU DE PRODUTOS ---

void mostrarMenuProdutos() {
    char *opcoes[] = {
        "1. Cadastrar Produto",
        "2. Consultar Produto",
        "3. Remover Produto",
        "4. Listar Produtos",
        "5. Voltar"
    };
    int n_opcoes = 5;

    int altura = 12, largura = 45;
    int inicio_y = (LINES - altura) / 2;
    int inicio_x = (COLS - largura) / 2;

    WINDOW *win = newwin(altura, largura, inicio_y, inicio_x);
    keypad(win, TRUE);

    int destaque = 0;
    int ch;

    while(1) {
        desenha_menu_generico(win, "MODULO DE PRODUTOS", opcoes, n_opcoes, destaque);
        ch = wgetch(win);

        switch(ch) {
            case KEY_UP:
                if (destaque > 0) destaque--;
                break;
            case KEY_DOWN:
                if (destaque < n_opcoes - 1) destaque++;
                break;
            case 10: // Enter
                if (destaque == 4) { // Voltar
                    delwin(win);
                    return;
                }

                // Tenta chamar as funções de produto se existirem no produto.h
                // Se der erro de "implicit declaration", comente a linha que der erro
                if (destaque == 0) inserirProduto(); 
                // if (destaque == 1) consultarProduto(); // Verifique se existe
                // if (destaque == 2) removerProduto();   // Verifique se existe
                // if (destaque == 3) listarProdutos();   // Verifique se existe

                clear();
                refresh();
                keypad(win, TRUE);
                break;
        }
    }
}

// --- MENU DE PEDIDOS ---

void mostrarMenuPedidos() {
    char *opcoes[] = {
        "1. Cadastrar Pedido",
        "2. Consultar Pedido",
        "3. Remover Pedido",
        "4. Listar Pedidos",
        "5. Voltar"
    };
    int n_opcoes = 5;

    int altura = 12, largura = 45;
    int inicio_y = (LINES - altura) / 2;
    int inicio_x = (COLS - largura) / 2;

    WINDOW *win = newwin(altura, largura, inicio_y, inicio_x);
    keypad(win, TRUE);

    int destaque = 0;
    int ch;

    while(1) {
        desenha_menu_generico(win, "MODULO DE PEDIDOS", opcoes, n_opcoes, destaque);
        ch = wgetch(win);

        switch(ch) {
            case KEY_UP:
                if (destaque > 0) destaque--;
                break;
            case KEY_DOWN:
                if (destaque < n_opcoes - 1) destaque++;
                break;
            case 10: // Enter
                if (destaque == 4) { // Voltar
                    delwin(win);
                    return;
                }

                if (destaque == 0) inserirPedido();
                if (destaque == 1) consultarPedido();
                if (destaque == 2) removerPedido();
                if (destaque == 3) listarPedidos();

                clear();
                refresh();
                keypad(win, TRUE);
                break;
        }
    }
}

// --- MENU PRINCIPAL ---

void mostrarMenuPrincipal() {
    char *opcoes[] = {
        "1. Modulo de Clientes",
        "2. Modulo de Produtos",
        "3. Modulo de Pedidos",
        "4. Sair do Sistema"
    };
    int n_opcoes = 4;

    int altura = 12, largura = 45;
    int inicio_y = (LINES - altura) / 2;
    int inicio_x = (COLS - largura) / 2;

    WINDOW *win = newwin(altura, largura, inicio_y, inicio_x);
    keypad(win, TRUE);

    int destaque = 0;
    int ch;

    while(1) {
        clear(); // Limpa o fundo do menu principal
        refresh();
        desenha_menu_generico(win, "MENU PRINCIPAL", opcoes, n_opcoes, destaque);
        ch = wgetch(win);

        switch(ch) {
            case KEY_UP:
                if (destaque > 0) destaque--;
                else destaque = n_opcoes - 1; // Loop
                break;
            case KEY_DOWN:
                if (destaque < n_opcoes - 1) destaque++;
                else destaque = 0; // Loop
                break;
            case 10: // Enter
                if (destaque == 3) { // Sair
                    delwin(win);
                    endwin();
                    exit(0);
                }

                // Limpa antes de entrar no submenu
                wclear(win);
                wrefresh(win);
                delwin(win); // Deleta janela principal temporariamente
                endwin(); // Reseta ncurses temporariamente (opcional, mas seguro)
                
                // Reinicia ncurses
                initscr(); cbreak(); noecho(); keypad(stdscr, TRUE);

                if (destaque == 0) mostrarMenuCliente();
                if (destaque == 1) mostrarMenuProdutos();
                if (destaque == 2) mostrarMenuPedidos();

                // Recria janela principal ao voltar
                clear();
                refresh();
                win = newwin(altura, largura, inicio_y, inicio_x);
                keypad(win, TRUE);
                break;
        }
    }
}