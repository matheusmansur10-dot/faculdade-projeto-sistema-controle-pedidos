#ifndef PRODUTO_H
#define PRODUTO_H
#define MAX_PRODUTOS 100

typedef struct
{
    int id;              // numero de identificação de cada produto
    char descricao[100]; // descrição do produto
    double preco;        // preço unitario do produto
    int estoque;         // quantidade desse produto disponível no estoque
} Produto;

extern Produto lista_produtos[MAX_PRODUTOS];
extern int qtd_produtos;
int analisarProduto(int id);
void inserirProduto();
void editarProduto();
void consultarProduto();
void listarProduto();
void removerProduto();
void mostrarMenuProdutos();

#endif // PRODUTO_H