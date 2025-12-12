#include <ncurses.h>
#include "cliente.h"
#include "produto.h"
#include "pedido.h"
#include "persistencia.h" 


void mostrarMenuCliente();   
void mostrarMenuPedidos();

int main() {
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    
    carregarClientes();
    carregarProdutos();
    carregarPedidos();

    mostrarMenuPrincipal();
    mostrarMenuCliente();
    mostrarMenuProdutos(); 
    mostrarMenuPedidos();

    
    salvarClientesCSV();
    salvarProdutos();
    salvarPedidos();

    
    endwin();
    return 0;
}