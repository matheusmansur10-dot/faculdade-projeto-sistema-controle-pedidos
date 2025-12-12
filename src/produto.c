#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h> // Biblioteca gráfica
#include "produto.h"
#include "persistencia.h"

Produto lista_produtos[MAX_PRODUTOS];
int qtd_produtos = 0;

// --- Funções Auxiliares ---

int analisarProduto(int id)
{
    for (int i = 0; i < qtd_produtos; i++)
    {
        if (lista_produtos[i].id == id)
        {
            return i; // Retorna o índice onde achou
        }
    }
    return -1; // Não encontrou
}

// --- Funções Visuais ---

void inserirProduto()
{
    if (qtd_produtos >= MAX_PRODUTOS)
    {
        clear();
        mvprintw(2, 2, "ERRO: Limite de produtos atingido!");
        getch();
        return;
    }

    Produto p;
    echo(); 
    curs_set(1);
    clear();
    box(stdscr, 0, 0);

    mvprintw(1, 2, "=== CADASTRAR PRODUTO ===");

    // Loop de validação do ID
    while(1) {
        mvprintw(3, 2, "ID do Produto:      "); // Espaços para limpar input anterior
        move(3, 17); // Posiciona cursor
        if (scanw("%d", &p.id) != 1) {
            mvprintw(LINES-2, 2, "Erro: Digite apenas numeros!");
            continue;
        }
        
        if (analisarProduto(p.id) != -1) {
            mvprintw(LINES-2, 2, "Erro: ID %d ja existe! Tente outro.", p.id);
            continue;
        }
        // Limpa linha de erro
        move(LINES-2, 0); clrtoeol(); 
        break;
    }

    mvprintw(5, 2, "Descricao: ");
    scanw(" %[^\n]", p.descricao);

    mvprintw(6, 2, "Preco (R$): ");
    scanw("%lf", &p.preco);

    mvprintw(7, 2, "Estoque: ");
    scanw("%d", &p.estoque);

    // Salvar
    lista_produtos[qtd_produtos] = p;
    qtd_produtos++;
    salvarProdutos(); // Salva no arquivo imediatamente

    noecho();
    curs_set(0);
    attron(A_BOLD);
    mvprintw(9, 2, ">>> Produto cadastrado com sucesso! <<<");
    attroff(A_BOLD);
    
    mvprintw(11, 2, "Pressione qualquer tecla...");
    getch();
}

void editarProduto()
{
    int id, indice;
    char confirmacao;

    echo(); curs_set(1);
    clear(); box(stdscr, 0, 0);
    mvprintw(1, 2, "=== EDITAR PRODUTO ===");
    
    mvprintw(3, 2, "ID do produto para editar: ");
    scanw("%d", &id);

    indice = analisarProduto(id);

    if (indice == -1) {
        noecho();
        mvprintw(5, 2, "ERRO: Produto ID %d nao encontrado.", id);
        getch();
        return;
    }

    Produto temp = lista_produtos[indice];
    char buffer[100]; // Buffer temporário para ler strings

    mvprintw(5, 2, "--- Dados Atuais ---");
    mvprintw(6, 2, "Descricao: %s", temp.descricao);
    mvprintw(7, 2, "Preco:     R$ %.2f", temp.preco);
    mvprintw(8, 2, "Estoque:   %d", temp.estoque);

    mvprintw(10, 2, "--- Novos Dados (Enter para manter) ---");

    // Editar Descrição
    mvprintw(12, 2, "Nova Descricao: ");
    getnstr(buffer, 99); // Leitura segura de string
    if(strlen(buffer) > 0) strcpy(temp.descricao, buffer);

    // Editar Preço
    mvprintw(13, 2, "Novo Preco: ");
    getnstr(buffer, 99);
    if(strlen(buffer) > 0) temp.preco = atof(buffer);

    // Editar Estoque
    mvprintw(14, 2, "Novo Estoque: ");
    getnstr(buffer, 99);
    if(strlen(buffer) > 0) temp.estoque = atoi(buffer);

    // Confirmar
    mvprintw(16, 2, "Confirma alteracao? (S/N): ");
    scanw(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        lista_produtos[indice] = temp;
        salvarProdutos();
        mvprintw(18, 2, "Produto atualizado com sucesso!");
    } else {
        mvprintw(18, 2, "Operacao cancelada.");
    }

    noecho(); curs_set(0);
    getch();
}

void consultarProduto()
{
    int id, indice;
    char conf;
    
    echo(); curs_set(1);
    clear(); box(stdscr, 0, 0);
    mvprintw(1, 2, "=== CONSULTAR PRODUTO ===");
    mvprintw(3, 2, "Digite o ID: ");
    scanw("%d", &id);
    noecho(); curs_set(0);

    indice = analisarProduto(id);

    if (indice != -1) {
        mvprintw(5, 2, "Produto Encontrado:");
        mvprintw(7, 2, "ID:        %d", lista_produtos[indice].id);
        mvprintw(8, 2, "Descricao: %s", lista_produtos[indice].descricao);
        mvprintw(9, 2, "Preco:     R$ %.2f", lista_produtos[indice].preco);
        mvprintw(10, 2, "Estoque:   %d", lista_produtos[indice].estoque);
        
        mvprintw(12, 2, "Deseja editar? (S/N): ");
        echo();
        scanw(" %c", &conf);
        noecho();
        
        if(conf == 'S' || conf == 's') {
            editarProduto(); // Chama a função de edição
            return;
        }
    } else {
        mvprintw(5, 2, "Produto nao encontrado.");
    }
    mvprintw(14, 2, "Pressione qualquer tecla...");
    getch();
}

void listarProdutos()
{
    clear(); box(stdscr, 0, 0);
    mvprintw(1, 2, "=== LISTA DE PRODUTOS ===");
    
    if (qtd_produtos == 0) {
        mvprintw(3, 2, "Nenhum produto cadastrado.");
    } else {
        attron(A_UNDERLINE);
        mvprintw(3, 2, "ID   | Descricao            | Preco      | Estoque");
        attroff(A_UNDERLINE);
        
        for (int i = 0; i < qtd_produtos; i++) {
            // Limita a exibição para não estourar a tela
            if (4+i >= LINES-2) break; 
            
            mvprintw(4+i, 2, "%-4d | %-20s | R$ %-7.2f | %d", 
                lista_produtos[i].id, 
                lista_produtos[i].descricao, 
                lista_produtos[i].preco, 
                lista_produtos[i].estoque);
        }
    }

    mvprintw(LINES-2, 2, "Total: %d produtos. Pressione qualquer tecla...", qtd_produtos);
    getch();
}

void removerProduto()
{
    int id, indice;
    char conf;

    echo(); curs_set(1);
    clear(); box(stdscr, 0, 0);
    mvprintw(1, 2, "=== REMOVER PRODUTO ===");
    mvprintw(3, 2, "ID para remover: ");
    scanw("%d", &id);
    noecho(); curs_set(0);

    indice = analisarProduto(id);

    if (indice != -1) {
        mvprintw(5, 2, "Produto: %s", lista_produtos[indice].descricao);
        mvprintw(6, 2, "Tem certeza? (S/N): ");
        echo(); scanw(" %c", &conf); noecho();

        if (conf == 'S' || conf == 's') {
            // Desloca o vetor para a esquerda
            for (int j = indice; j < qtd_produtos - 1; j++) {
                lista_produtos[j] = lista_produtos[j + 1];
            }
            qtd_produtos--;
            salvarProdutos(); // Salva alteração
            mvprintw(8, 2, "Produto removido com sucesso!");
        } else {
            mvprintw(8, 2, "Operacao cancelada.");
        }
    } else {
        mvprintw(5, 2, "Produto nao encontrado.");
    }
    getch();
}