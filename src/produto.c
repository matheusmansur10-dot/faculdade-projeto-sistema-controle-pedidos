#include "produto.h"

#define MAX_PRODUTOS 100 // determina o tamanho maximo do array estático

static Produto lista_produtos[MAX_PRODUTOS]; // variavel do tipo produto

static int qtd_produtos = 0; // numero de produtos cadastrados

int analisarProdutos(int id)
{
    for (int i = 0; i < qtd_produtos; i++)
    {
        if (lista_produtos.id[i] == id)
        {
            return 1;
        }
    }
    return 0;
}
