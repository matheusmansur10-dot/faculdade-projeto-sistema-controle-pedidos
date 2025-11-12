#ifndef PEDIDO_H
#define PEDIDO_H

typedef struct
{
    int id; // identificação do pedido
    int clienteId; // id do cliente
    char data[11];  // data do pedido "dd/mm/aaaa"
    double total; // valor total do pedido
} Pedido;


typedef struct 
{
    int pedidoId;  // id do pedido ao qual o item pertence
    int produtoId; // id do produto comprado
    int quantidade; // quantidade do produto
    double subtotal; // valor (quantidade * preco do produto)
} ItemPedido;

int analisarPedido(int id);

#endif // PEDIDO_H
