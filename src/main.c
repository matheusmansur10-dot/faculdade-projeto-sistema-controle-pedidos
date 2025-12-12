#include <ncurses.h> // Inclui a biblioteca de interface
#include "interface.h" 
#include "pedido.h"

int main() {
 
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    carregarPedidos();

    mostrarMenuPedidos();
    mostrarMenuProdutos();
    mostrarMenuCliente();

    salvarPedidos();

    
    endwin();
    return 0;
}