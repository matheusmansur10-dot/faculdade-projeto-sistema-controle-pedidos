#ifndef PEDIDO_H
#define PEDIDO_H

#define MAX_PEDIDOS 100 

typedef struct
{
    int id; 
    int clienteId; 
    char data[11];  
    double total; 
} Pedido;

typedef struct 
{
    int pedidoId;  
    int produtoId; 
    int quantidade; 
    double subtotal; 
} ItemPedido;

int analisarPedido(int id);
void inserirPedido();
void consultarPedido();
void listarPedidos();
void removerPedido();


void salvarPedidos();
void carregarPedidos();


extern Pedido lista_pedidos[MAX_PEDIDOS]; 
extern int num_pedidos;


#endif // PEDIDO_H