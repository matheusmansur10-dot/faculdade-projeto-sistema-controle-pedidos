#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "pedido.h"
#include "cliente.h" 

// Função para mostrar o menu do cliente em nCruses
// Esse menu usa nCurses e funciona assim:
// Seta CIMA e BAIXO muda a opção selecionada
// ENTER confirma
// O item selecionado fica destacado
void mostrarMenuCliente() {

    // inicializa a biblioteca ncurses
    initscr();            // inicia a tela
    noecho();             // não mostra teclas digitadas
    cbreak();             // leitura imediata de teclas
    keypad(stdscr, TRUE); // ativa setas do teclado
    curs_set(0);          // esconde o cursor

    // ativa cor se disponível
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_CYAN);  // cor da opção selecionada
    }

    int opcao = 0;      // guarda qual linha está selecionada
    int tecla;          // captura a tecla pressionada

    // lista das opções do menu
    const char *opcoes[] = {
        "Cadastrar Cliente",
        "Consultar Cliente",
        "Remover Cliente",
        "Listar Clientes",
        "Sair"
    };

    int totalOpcoes = 5;

    while (1) {  // laço principal do menu

        clear(); // limpa a tela

        // título do menu
        mvprintw(1, 2, "=== MENU DO CLIENTE (Ncurses) ===");
        mvprintw(3, 2, "Use as setas ↑ e ↓ para navegar. ENTER para selecionar.");

        // desenha as opções na tela
        for (int i = 0; i < totalOpcoes; i++) {

            if (i == opcao) {
                // destaca a opção selecionada
                attron(COLOR_PAIR(1));
                mvprintw(6 + i, 4, "> %s", opcoes[i]);
                attroff(COLOR_PAIR(1));
            } else {
                mvprintw(6 + i, 4, "  %s", opcoes[i]);
            }
        }

        // refresh atualiza a tela
        refresh();

        // pega a tecla pressionada
        tecla = getch();

        // movimentação com setas
        if (tecla == KEY_UP) {
            opcao--;
            if (opcao < 0)
                opcao = totalOpcoes - 1;  // volta para o último
        }
        else if (tecla == KEY_DOWN) {
            opcao++;
            if (opcao >= totalOpcoes)
                opcao = 0;          // volta para o primeiro
        }
        else if (tecla == '\n') {   // ENTER seleciona

            // limpa a tela para rodar a ação
            clear();
            refresh();

            // executa conforme a opção escolhida
            switch (opcao) {

                case 0: // Cadastrar
                    endwin();        // fecha ncurses para poder usar scanf
                    cadastrarCliente();
                    initscr();
                    keypad(stdscr, TRUE);
                    noecho();
                    break;

                case 1: // Consultar
                    endwin();
                    consultarCliente();
                    initscr();
                    keypad(stdscr, TRUE);
                    noecho();
                    break;

                case 2: // Remover
                    endwin();
                    removerCliente();
                    initscr();
                    keypad(stdscr, TRUE);
                    noecho();
                    break;

                case 3: // Listar
                    endwin();
                    listarClientes();
                    printf("\nPressione ENTER para voltar ao menu...");
                    getchar();
                    initscr();
                    keypad(stdscr, TRUE);
                    noecho();
                    break;

                case 4: // Sair
                    endwin();               // fecha ncurses antes de sair
                    salvarClientesCSV();    // salva tudo no CSV
                    return;                 // sai da função (volta ao main)
            }
        }
    }

    endwin(); // encerra ncurses
}


char *opcoes_pedido[] = {
    "1. Cadastrar Pedido",
    "2. Consultar Pedido",
    "3. Remover Pedido",
    "4. Listar Pedidos",
    "5. Voltar ao Menu Principal"};
int num_opcoes = sizeof(opcoes_pedido) / sizeof(char *);

void desenha_menu_pedidos(WINDOW *menu_win, int destacado)
{
    int x = 2, y = 2;
    box(menu_win, 0, 0);

    mvwprintw(menu_win, 1, (40 - 18) / 2, "MÓDULO DE PEDIDOS");

    for (int i = 0; i < num_opcoes; i++)
    {
        if (destacado == i)
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
