#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int id;                // identificação do cliente
    char tipo_cliente;     // "F" = pessoa física; "J" = pessoa jurídica

    char nome[100];        // nome do cliente 
    char endereco[200];    // endereço do cliente
    char telefone[20];     // telefone do cliente

    // Campos exclusivos dependendo do tipo de cliente 
    char CPF[15];           // ex: 000.000.000-00
    char CNPJ[20];          // ex: 00.000.000/0000-00
    char razao_social[100]; // nome oficial da empresa 
    
} Cliente;

#endif // CLIENTE_H