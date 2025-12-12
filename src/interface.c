#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "pedido.h"
#include "cliente.h" 

// Função para mostrar o menu cliente em nCurses
void mostrarMenuClientes() 
{

    int escolha = 0;      // índice da opção selecionada
    int tecla;            // guarda tecla pressionada
    const int totalOp = 5;

    // Opções do menu
    char *opcoes[] = {
        "1. Cadastrar Cliente",
        "2. Consultar Cliente",
        "3. Remover Cliente",
        "4. Listar Clientes",
        "5. Voltar ao Menu Principal"
    };

    // Iniciar a interface ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (1) 
    {
        clear();

        // Desenhando a borda e o título do menu 
        int altura = 12, largura = 45;
        int starty = (LINES - altura) / 2;
        int startx = (COLS - largura) / 2;

        WINDOW *menuwin = newwin(altura, largura, starty, startx);
        box(menuwin, 0, 0);

        mvwprintw(menuwin, 1, 12, "MODULO DE CLIENTES");

        // Mostrar as opções e destacar a selecionada no menu
        for (int i = 0; i < totalOp; i++) 
        {
            if (i == escolha) 
            {
                // Destaque da opção selecionada
                wattron(menuwin, A_REVERSE);
                mvwprintw(menuwin, i + 3, 2, "%s", opcoes[i]);
                wattroff(menuwin, A_REVERSE);
            } else {
                mvwprintw(menuwin, i + 3, 2, "%s", opcoes[i]);
            }
        }

        mvwprintw(menuwin, altura - 2, 2, "Use as setas e Enter");

        wrefresh(menuwin);

        // Espera o usuário apertar uma tecla
        tecla = getch();

        // Controle do menu com setas para cima ou para baixo
        switch (tecla) 
        {
            case KEY_UP:
                escolha--;
                if (escolha < 0) escolha = totalOp - 1;
                break;

            case KEY_DOWN:
                escolha++;
                if (escolha == totalOp) escolha = 0;
                break;
            
                case 10:  // tecla ENTER
                // Fechar interface temporariamente
                endwin();
                
                // Execultar a ação escolhida 
                switch (escolha) 
                {
                    case 0:
                        cadastrarCliente();
                        break;
                    
                    case 1:
                        consultarCliente();
                        break;
                    
                    case 2:
                        removerCliente();
                        break;
                    
                    case 3:
                        listarClientes();
                        break;
                
                    case 4:
                        return; // volta ao menu principal
                }
                // Após fazer a ação, reabrir a interface
                initscr();
                cbreak();
                noecho();
                keypad(stdscr, TRUE);
                break;
        }
    }
    // fechar a interface
    endwin();
}


void mostrarMenuPedidos()
{
    WINDOW *menu_win;
    int altura = 10;
    int largura = 40;

    // Centralizar janela
    int inicio_y = (LINES - altura) / 2;
    int inicio_x = (COLS - largura) / 2;

    // Criar a janela
    menu_win = newwin(altura, largura, inicio_y, inicio_x);
    keypad(menu_win, TRUE); // Ativa o uso das setas

    int destacado = 0;
    int ch;

    // loop do menu
    while (1)
    {
        desenha_menu_pedidos(menu_win, destacado);
        ch = wgetch(menu_win);

        switch (ch)
        {
        case KEY_UP:
            if (destacado > 0)
                destacado--;
            break;
        case KEY_DOWN:
            if (destacado < num_opcoes - 1)
                destacado++;
            break;
        case 10: // Tecla ENTER
                // Se escolheu "Voltar" (a última opção)
                if (destacado == num_opcoes - 1) { 
                    goto fim_menu; 
                }
                
                // Se escolheu "Cadastrar Pedido" (Opção 0)
                if (destacado == 0) {
                    inserirPedido(); 
                    
                    // a caixa e limpar a tela para o menu não ficar bugado.
                    clear(); 
                    keypad(menu_win, TRUE); // Reativa as setas
                }
                if (destacado == 1) { // Consultar (Opção 1)
                    consultarPedido();
                    clear();
                    keypad(menu_win, TRUE);
                }
                if (destacado == 2) { 
                    removerPedido();
                    clear();
                    keypad(menu_win, TRUE);
                }
                if (destacado == 3) { 
                    listarPedidos();
                    clear();
                    keypad(menu_win, TRUE);
                }
            break;
        }
    }
fim_menu:
    delwin(menu_win); // remove a janela
}

// Interface Menu Principal Produtos
char *opcoes_produto[] = {
    "1. Cadastrar Produto",
    "2. Consultar Produto",
    "3. Remover Produto",
    "4. Listar Produtos",
    "5. Sair",
};
int num_opcoes_prod = sizeof(opcoes_produto) / sizeof(char *);
void desenha_menu_produtos(WINDOW *menu_j, int destacado, int n_opcoes)
{
    int x = 2, y = 2;
    box(menu_j, 0, 0);
    // título
    mvwprintw(menu_j, 1, (40 - 18) / 2, "MODULO DE PRODUTOS");
    // opções
    for (int cont = 0; cont < n_opcoes; cont++)
    {
        if (cont == destacado)
        {
            wattron(menu_j, A_REVERSE); // A_REVERSE é usada para destacar a opção selecionada no menu
            mvwprintw(menu_j, y + cont + 1, x, " > %s", opcoes_produto[cont]);
            wattroff(menu_j, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_j, y + cont + 1, x, "  %s", opcoes_produto[cont]);
        }
    }
    // instruções
    mvwprintw(menu_j, 8, 2, "Use setas e Enter");
    wrefresh(menu_j);
}

void mostrarMenuProdutos()
{
    WINDOW *menu_j;
    int altura = 10;
    int largura = 40;

    int inicio_y = (LINES - altura) / 2;
    int inicio_x = (COLS - largura) / 2;

    menu_j = newwin(altura, largura, inicio_y, inicio_x);
    keypad(menu_j, TRUE);

    int destacado = 0;
    int ch = 0;

    while (1)
    {
        desenha_menu_produtos(menu_j, destacado, num_opcoes_prod);
        ch = wgetch(menu_j);
        switch (ch)
        {
        case KEY_UP:
            if (destacado > 0)
                destacado--;
            break;
        case KEY_DOWN:
            if (destacado < num_opcoes_prod - 1)
                destacado++;
            break;
        case 10:
            if (destacado == num_opcoes_prod - 1)
            {
                goto fim_menu;
            }
            break;
        }
    }
fim_menu:
    delwin(menu_j);
}
