#include "pedido.h"

#define MAX_PEDIDOS 100

static Pedido lista_pedidos[MAX_PEDIDOS]; //banco de dados local
static int num_pedidos = 0; //contdor pedidos


int analisarPedidos(int id)
{
    for(int i = 0; i < num_pedidos; i++)
    {
        if(lista_pedidos[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}


