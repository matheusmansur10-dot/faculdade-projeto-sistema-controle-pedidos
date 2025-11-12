#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct
{
    int id;              // numero de indetificação de cada produto
    char descricao[100]; // descrição do produto
    double preco;        // preço unitario do produto
    int estoque;         // quantidade desse produto disponível no estoque
} Produto;
#endif // PRODUTO_H