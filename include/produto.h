#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_PRODUTOS 100 

typedef struct {
    int id;
    char descricao[100];
    double preco;
    int estoque;
} Produto;

// Funções
int analisarProduto(int id);
void inserirProduto(); 
void editarProduto();
void consultarProduto();
void listarProdutos();
void removerProduto();


extern Produto lista_produtos[MAX_PRODUTOS];
extern int qtd_produtos;

#endif