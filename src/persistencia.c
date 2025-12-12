#include <stdio.h>
#include <stdlib.h>
#include "persistencia.h"
#include "cliente.h"
#include "produto.h"
#include "pedido.h"

// --- CLIENTES ---

void salvarClientesCSV() {
    FILE *arquivo = fopen("data/Clientes.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir data/Clientes.csv\n");
        return;
    }
    // Salva PF
    for (int i = 0; i < totalPF; i++) {
        fprintf(arquivo, "F;%d;%s;%s;%s;%s;%s\n",
            listaPF[i].base.id, listaPF[i].nome, listaPF[i].cpf,
            listaPF[i].base.endereco, listaPF[i].base.telefone, listaPF[i].base.email);
    }
    // Salva PJ
    for (int i = 0; i < totalPJ; i++) {
        fprintf(arquivo, "J;%d;%s;%s;%s;%s;%s\n",
            listaPJ[i].base.id, listaPJ[i].razaoSocial, listaPJ[i].cnpj,
            listaPJ[i].base.endereco, listaPJ[i].base.telefone, listaPJ[i].base.email);
    }
    fclose(arquivo);
}

void carregarClientes() {
    FILE *arquivo = fopen("data/Clientes.csv", "r");
    if (arquivo == NULL) { totalPF = 0; totalPJ = 0; return; }

    totalPF = 0; totalPJ = 0;
    char tipo;
    while (fscanf(arquivo, " %c;", &tipo) != EOF) {
        if (tipo == 'F') {
            fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%[^;];%[^\n]", 
                &listaPF[totalPF].base.id, listaPF[totalPF].nome, listaPF[totalPF].cpf,
                listaPF[totalPF].base.endereco, listaPF[totalPF].base.telefone, listaPF[totalPF].base.email);
            totalPF++;
        } else if (tipo == 'J') {
            fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%[^;];%[^\n]", 
                &listaPJ[totalPJ].base.id, listaPJ[totalPJ].razaoSocial, listaPJ[totalPJ].cnpj,
                listaPJ[totalPJ].base.endereco, listaPJ[totalPJ].base.telefone, listaPJ[totalPJ].base.email);
            totalPJ++;
        }
    }
    fclose(arquivo);
}

// --- PRODUTOS (CORRIGIDO: REMOVIDO CAMPO NOME) ---

void salvarProdutos() {
    FILE *arquivo = fopen("data/Produtos.csv", "w");
    if (arquivo == NULL) return;
    
    // Cabeçalho: ID, Descricao, Preco, Estoque
    fprintf(arquivo, "ID,Descricao,Preco,Estoque\n");
    
    for (int i = 0; i < qtd_produtos; i++) {
        // AQUI ESTAVA O ERRO: Removi lista_produtos[i].nome
        fprintf(arquivo, "%d,%s,%.2f,%d\n", 
            lista_produtos[i].id, 
            lista_produtos[i].descricao, 
            lista_produtos[i].preco, 
            lista_produtos[i].estoque);
    }
    fclose(arquivo);
}

void carregarProdutos() {
    FILE *arquivo = fopen("data/Produtos.csv", "r");
    if (arquivo == NULL) { qtd_produtos = 0; return; }

    qtd_produtos = 0;
    char buffer[256];
    fscanf(arquivo, "%[^\n]\n", buffer); // Pula cabeçalho

    // AQUI TAMBÉM: Lê apenas 4 campos agora
    while (fscanf(arquivo, "%d,%49[^,],%lf,%d\n", 
            &lista_produtos[qtd_produtos].id, 
            lista_produtos[qtd_produtos].descricao,
            &lista_produtos[qtd_produtos].preco,
            &lista_produtos[qtd_produtos].estoque) == 4) {
        
        qtd_produtos++;
    }
    fclose(arquivo);
}

// --- PEDIDOS ---

void salvarPedidos() {
    FILE *arquivo = fopen("data/Pedidos.csv", "w");
    if (arquivo == NULL) return;

    fprintf(arquivo, "ID,ClienteID,Data,Total\n");
    for (int i = 0; i < num_pedidos; i++) {
        fprintf(arquivo, "%d,%d,%s,%.2f\n", 
            lista_pedidos[i].id, lista_pedidos[i].clienteId,
            lista_pedidos[i].data, lista_pedidos[i].total);
    }
    fclose(arquivo);
}

void carregarPedidos() {
    FILE *arquivo = fopen("data/Pedidos.csv", "r");
    if (arquivo == NULL) { num_pedidos = 0; return; }

    char buffer[100];
    fscanf(arquivo, "%s\n", buffer); // Pula cabeçalho
    num_pedidos = 0;
    while (fscanf(arquivo, "%d,%d,%[^,],%lf\n", 
             &lista_pedidos[num_pedidos].id, &lista_pedidos[num_pedidos].clienteId,
             lista_pedidos[num_pedidos].data, &lista_pedidos[num_pedidos].total) == 4) {
        num_pedidos++;
    }
    fclose(arquivo);
}