#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "persistencia.h"
#define MAX_PRODUTOS 100 // determina o tamanho maximo do array estático

Produto lista_produtos[MAX_PRODUTOS]; // variavel do tipo produto
int qtd_produtos = 0;                 // numero de produtos cadastrados

int analisarProduto(int id)
{
    for (int i = 0; i < qtd_produtos; i++)
    {
        if (lista_produtos[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

// função para cadastrar produto
void inserirProduto()
{
    Produto novo_produto;

    printf("\n==== CADASTRAR PRODUTO ====\n");

    if (qtd_produtos >= MAX_PRODUTOS) // verifica se mais produtos podem ser cadastrados
    {
        printf("ERRO: O limite máximo de %d produtos foi atingido. Não é possível cadastrar.\n", MAX_PRODUTOS);
        return;
    }

    for (;;)
    {
        printf("\nInforme o código (ID) do produto: ");

        // verifica se a leitura é válida (não é número)
        if (scanf("%d", &novo_produto.id) != 1)
        {
            printf("Entrada inválida. Tente novamente com um número inteiro.\n");
            while (getchar() != '\n' && getchar() != EOF)
                ; // limpa o buffer
        }
        // verifica se o produto já foi cadastrado. Se sim, a função a retornará 1
        if (analisarProduto(novo_produto.id) != -1)
        {
            printf("ERRO: O código %d já existe. Por favor, digite um novo código.\n", novo_produto.id);
        }
        else
        {
            // código único e válido: Sai do loop
            break;
        }
    }
    printf("Informe a descrição do produto: ");
    scanf(" %[^\n]", novo_produto.descricao);

    printf("Informe o preço (R$): ");
    scanf("%lf", &novo_produto.preco);

    printf("Informe a quantidade em estoque: ");
    scanf("%d", &novo_produto.estoque);

    lista_produtos[qtd_produtos] = novo_produto; // caso o produto ainda não tenha sido cadastrado, ele será adicionado ao banco de dados lista_produtos
    qtd_produtos++;
    printf("\nProduto cadastrado com sucesso!\n");
    return;
}

void editarProduto()
{
    int id_edicao;
    int indice;
    char confirmacao;

    printf("\n==== EDITAR PRODUTO ====\n");

    printf("Digite o ID do produto que deseja editar: ");

    if (scanf("%d", &id_edicao) != 1) // garante que um inteiro seja lido
    {
        printf("\nERRO: Entrada inválida. Digite um número inteiro.\n");
        while (getchar() != '\n' && getchar() != EOF)
            ;
        return;
    }

    indice = analisarProduto(id_edicao);

    if (indice != -1) // quando o produto for encontrado
    {
        // criação de uma cópia do item para trabalhar nela. O item original fica no vetor.
        Produto produto_temp = lista_produtos[indice];

        printf("\nProduto encontrado - ID %d.\n", lista_produtos[indice].id);
        printf("=======================================\n");
        printf("Descrição atual: %s\n", lista_produtos[indice].descricao);
        printf("Preço atual: R$ %.2f\n", lista_produtos[indice].preco);
        printf("Estoque atual: %d\n", lista_produtos[indice].estoque);

        printf("\n-- Novas Informações --\n");

        char nova_descricao[100];
        printf("Nova Descrição (Enter para manter atual: %s): ", lista_produtos[indice].descricao);

        if (scanf(" %[^\n]", nova_descricao) == 1 && strlen(nova_descricao) > 0)
        {
            // a alteração é feita na CÓPIA TEMPORÁRIA
            strcpy(produto_temp.descricao, nova_descricao);
        }
        while (getchar() != '\n' && getchar() != EOF)
            ;

        float novo_preco;
        printf("Novo Preço (R$ %.2f para manter): ", lista_produtos[indice].preco);

        // checa se a leitura foi bem-sucedida e se o valor é positivo/diferente de zero (para manter)
        if (scanf("%f", &novo_preco) == 1 && novo_preco > 0)
        {
            produto_temp.preco = novo_preco;
        }
        else
        {
            while (getchar() != '\n' && getchar() != EOF)
                ;
        }

        int nova_quantidade;
        printf("Novo Estoque (%d para manter): ", lista_produtos[indice].estoque);

        // Checa se a leitura foi bem-sucedida e se o valor é não-negativo/diferente de zero
        if (scanf("%d", &nova_quantidade) == 1 && nova_quantidade >= 0 && nova_quantidade != 0)
        {
            // A alteração é feita na CÓPIA TEMPORÁRIA
            produto_temp.estoque = nova_quantidade;
        }
        else
        {
            // limpa o buffer se a leitura falhar
            while (getchar() != '\n' && getchar() != EOF)
                ;
        }

        // limpa o buffer final antes da confirmação
        while (getchar() != '\n' && getchar() != EOF)
            ;

        // nenhuma alteração foi salva no vetor principal ainda

        printf("\nConfirma as alterações? (S/N): ");
        scanf(" %c", &confirmacao);

        if (confirmacao == 'S' || confirmacao == 's')
        {
            // se confirmado, copia a versão modificada de volta para o vetor
            lista_produtos[indice] = produto_temp;
            printf("\nProduto com ID %d atualizado com sucesso.\n", lista_produtos[indice].id);
        }
        else
        {
            // não faz nada. O item original é mantido.
            printf("\nOperação de edição cancelada. Os dados foram mantidos.\n");
        }
    }
    else
    {
        printf("\nERRO: Produto com ID %d não encontrado no sistema.\n", id_edicao);
    }

    return;
}

void consultarProduto()
{
    int id_consulta;
    int indice;
    char confirmacao;

    printf("\n==== CONSULTAR PRODUTO ====\n");
    printf("Digite o ID do produto: ");

    // verificação do valor digitado pelo usuario

    if (scanf("%d", &id_consulta) != 1)
    {
        printf("\nERRO: Entrada inválida. Digite um número inteiro.\n");
        while (getchar() != '\n' && getchar() != EOF)
            ;
        return;
    }
    // limpa o buffer após leitura bem-sucedida do ID
    while (getchar() != '\n' && getchar() != EOF)
        ;

    indice = analisarProduto(id_consulta);

    if (indice != -1) // produto encontrado
    {
        // o índice retornado é usado para acessar os dados
        printf("\nProduto encontrado:\n");
        printf("ID: %d\n", lista_produtos[indice].id);
        printf("Descrição: %s\n", lista_produtos[indice].descricao);
        printf("Preço: R$ %.2f\n", lista_produtos[indice].preco);
        printf("Estoque: %d unidades\n", lista_produtos[indice].estoque);
        printf("\n--------------------------\n");
        printf("Deseja editar este produto (S/N)? ");
        scanf(" %c", &confirmacao);
        while (getchar() != '\n' && getchar() != EOF)
            ;
        if (confirmacao == 'S' || confirmacao == 's')
        {
            editarProduto(indice);
        }
        else
        {
            printf("Retornando ao menu principal.\n");
        }
    }
    else // produto não encontrado
    {
        printf("\n ERRO: Produto com ID %d não encontrado no sistema.\n", id_consulta);
    }
    return;
}

void listarProdutos()
{
    printf("\n==== LISTAGEM DE PRODUTOS CADASTRADOS ====\n");

    // verifica se há produtos cadastrados
    if (qtd_produtos == 0)
    {
        printf("\nNenhum produto encontrado no sistema.\n");
        return;
    }

    // Título da Tabela
    printf("------------------------------------------------------------------------\n");
    printf("| %-4s | %-30s | %-10s | %-10s |\n", "ID", "DESCRIÇÃO", "PREÇO (R$)", "ESTOQUE");
    printf("------------------------------------------------------------------------\n");

    // o loop 'for' percorre o vetor de produtos até a quantidade total cadastrada
    for (int i = 0; i < qtd_produtos; i++)
    {
        // exibe os dados do produto atual
        printf("| %-4d | %-30s | R$ %-7.2f | %-10d |\n",
               lista_produtos[i].id,
               lista_produtos[i].descricao,
               lista_produtos[i].preco,
               lista_produtos[i].estoque);
    }

    printf("------------------------------------------------------------------------\n");
    printf("\nTotal de %d produto(s) listado(s).\n", qtd_produtos);

    return;
}

void removerProduto()
{
    int id_remocao;
    int indice;
    char confirmacao;

    printf("\n==== REMOVER PRODUTO ====\n");

    printf("Digite o ID do produto a ser removido: ");

    if (scanf("%d", &id_remocao) != 1)
    {
        printf("\nERRO: Entrada inválida. Digite um número inteiro.\n");
        return;
    }

    // limpa o buffer após o scanf
    while (getchar() != '\n' && getchar() != EOF)
        ;

    // o sistema analisa o produto
    indice = analisarProduto(id_remocao);

    if (indice != -1) // produto encontrado
    {
        printf("\nProduto encontrado: ID %d | Descrição: %s\n", lista_produtos[indice].id, lista_produtos[indice].descricao);
        printf("Tem certeza que deseja remover este produto (S/N)? ");
        scanf(" %c", &confirmacao);

        if (confirmacao == 'S' || confirmacao == 's')
        {
            // o produto é retirado do cadastro

            // loop de deslocamento para a esquerda
            for (int j = indice; j < qtd_produtos - 1; j++)
            {
                lista_produtos[j] = lista_produtos[j + 1];
            }
            qtd_produtos--;
            printf("\nProduto com ID %d removido com sucesso.\n", id_remocao);
        }
        else
        {
            printf("\nOperação de remoção cancelada. Produto mantido.\n");
        }
    }
    else // caso não exista o produto
    {
        printf("\nERRO: Produto com ID %d não encontrado no sistema.\n", id_remocao);
    }

    return;
}