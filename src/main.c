#include <ncurses.h> 
#include "interface.h" 
#include "pedido.h"

int main() 
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    carregarClientes();
    carregarPedidos();

    mostrarMenuPedidos();
    mostrarMenuProdutos();
    mostrarMenuCliente();

    salvarPedidos();

    
    endwin();
    return 0;
}