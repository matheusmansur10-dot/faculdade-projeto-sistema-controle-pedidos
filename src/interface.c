#include <ncurses.h>
#include <string.h>
#include "interface.h"

char *opcoes_pedido[] = {
    "1. Cadastrar Pedido",
    "2. Consultar Pedido",
    "3. Remover Pedido",
    "4. Listar Pedidos",
    "5. Voltar ao Menu Principal"
};
int num_opcoes = sizeof(opcoes_pedido) / sizeof(char *);

void desenha_menu_pedidos(WINDOW *menu_win, int destacado) 
{
    int x = 2, y = 2;
    box(menu_win, 0, 0);

    mvwprintw(menu_win, 1, (40 - 18) / 2, "MÓDULO DE PEDIDOS");

    for(int i = 0; i < num_opcoes; i++)
    {
        if(destacado == i)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y + i + 1, x, " > %s", opcoes_pedido[i]);
            wattroff(menu_win, A_REVERSE);
        }
            else
            {
                mvwprintw(menu_win, y + i + 1, x, "   %s", opcoes_pedido[i]);
            }
    }
    mvwprintw(menu_win, 8, 2, "-Utilize as setas e Enter-");
    wrefresh(menu_win);
}

void mostrarMenuPedidos()
{
    WINDOW *menu_win;
    int altura = 10;
    int largura = 40;

    //Centralizar janela
    int inicio_y = (LINES - altura) / 2;
    int inicio_x = (COLS - largura) / 2;
    
    //Criar a janela
    menu_win = newwin(altura, largura, inicio_y, inicio_x);
    keypad(menu_win, TRUE);  //Ativa o uso das setas

    int destacado = 0;
    int ch;

    //loop do menu
    while(1)
    {
        desenha_menu_pedidos(menu_win, destacado);
        ch = wgetch(menu_win);

        switch(ch)
        {
            case KEY_UP: 
            if(destacado > 0)
                destacado--;
            break;
            case KEY_DOWN:
            if(destacado < num_opcoes - 1)
                destacado++;
            break;
            case 10: //enter
            if(destacado == num_opcoes - 1)
            {
                goto fim_menu;
            }
            break;
        }
    }
    fim_menu:
        delwin(menu_win); //remove a janela
}