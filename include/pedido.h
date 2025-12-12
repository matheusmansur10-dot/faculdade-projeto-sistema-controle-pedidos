#ifndef PEDIDO_H
#define PEDIDO_H

#define MAX_PEDIDOS 100

typedef struct {
    int id;
    int clienteId;
    char data[15]; 
    // Vamos salvar apenas o básico para garantir que funcione
    double total;
    int qtdProdutos;
    int produtosIds[10]; // Lista de IDs dos produtos comprados
} Pedido;

// Funções
void inserirPedido();
void consultarPedido();
void listarPedidos();
void removerPedido();


extern Pedido lista_pedidos[MAX_PEDIDOS];
extern int num_pedidos;

#endif