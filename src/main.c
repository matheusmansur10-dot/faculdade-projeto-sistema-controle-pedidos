#include <ncurses.h> // Inclui a biblioteca de interface
#include "interface.h" 

int main() {
 
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    mostrarMenuPedidos();
    mostrarMenuProdutos();
    
    endwin();
    return 0;
}