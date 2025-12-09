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

int inserirProduto(Produto novo_produto)
{
    if (qtd_produtos >= MAX_PRODUTOS) // verifica se mais produtos podem ser cadastrados
    {
        return 0;
    }

    if (analisarProduto(novo_produto.id) == 1) // verifica se o produto já foi cadastrado. Se sim, a função a retornará 1
    {
        return 0;
    }
    lista_produtos[qtd_produtos] = novo_produto; // caso o produto ainda não tenha sido cadastrado, ele será adicionado ao banco de dados lista_produtos
    qtd_produtos++;
    return 1;
}
