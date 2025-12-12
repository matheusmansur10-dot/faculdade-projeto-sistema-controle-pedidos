#include <ncurses.h>
#include "cliente.h"
#include "produto.h"
#include "pedido.h"
#include "persistencia.h" // Importante: O cabeçalho novo

int main() {
    // --- Inicialização do Ncurses ---
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // --- 1. CARREGAR DADOS (Ao abrir o programa) ---
    // Chama as funções do persistencia.c para ler os arquivos da pasta data/
    carregarClientes();
    carregarProdutos();
    carregarPedidos();

    
    mostrarMenuCliente();
    mostrarMenuProdutos(); 
    mostrarMenuPedidos();

    
    salvarClientesCSV();
    salvarProdutos();
    salvarPedidos();

    
    endwin();
    return 0;
}