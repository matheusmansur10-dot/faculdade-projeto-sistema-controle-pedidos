#include "produto.h"

#define MAX_PRODUTOS 100 // determina o tamanho maximo do array estático

static Produto lista_produtos[MAX_PRODUTOS]; // variavel do tipo produto

static int qtd_produtos = 0; // numero de produtos cadastrados

int analisarProduto(int id)
{
    for (int i = 0; i < qtd_produtos; i++)
    {
        if (lista_produtos[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

static Produto novo_produto;

int cadastrarProduto(Produto novo_produto)
{
    if (qtd_produtos >= MAX_PRODUTOS)
    {
        return 0;
    }

    if (novo_produto == analisarProduto(novo_produto))
        else
        {
            lista_produtos[qtd_produtos] = novo_produto;
        }
}
