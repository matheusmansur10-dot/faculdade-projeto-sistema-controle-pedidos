// persistencia.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "persistencia.h"
#include "cliente.h"

// Salvar todos os clientes em CSV
// Esta função grava todos os clientes PF e PJ no arquivo Clientes.csv.
// Cada linha contém os dados em formato texto separados por ponto e vírgula.
// Arquivo é sobrescrito toda vez que o sistema fecha.
void salvarClientesCSV() 
{
    FILE *arquivo = fopen("Clientes.csv", "w");

    if (arquivo == NULL) 
    {
        printf("Erro ao abrir arquivo CSV para salvar!\n");
        return;
    }

    // Salvando pessoa física 
    for (int i = 0; i < totalPF; i++) 
    {
        fprintf(arquivo,
            "F;%d;%s;%s;%s;%s;%s\n",
            listaPF[i].base.id,
            listaPF[i].nome,
            listaPF[i].cpf,
            listaPF[i].base.endereco,
            listaPF[i].base.telefone,
            listaPF[i].base.email
        );
    }

    // Salvando pessoa jurídica 
    for (int i = 0; i < totalPJ; i++) 
    {
        fprintf(arquivo,
            "J;%d;%s;%s;%s;%s;%s\n",
            listaPJ[i].base.id,
            listaPJ[i].razaoSocial,
            listaPJ[i].cnpj,
            listaPJ[i].base.endereco,
            listaPJ[i].base.telefone,
            listaPJ[i].base.email
        );
    }

    fclose(arquivo);
    printf("Clientes salvos no arquivo CSV com sucesso!\n");
}
