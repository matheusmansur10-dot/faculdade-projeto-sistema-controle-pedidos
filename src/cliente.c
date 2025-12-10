#include <stdio.h>
#include <string.h>
#include "cliente.h"

// Vetores dos clientes 
PessoaFisica listaPF[MAX_CLIENTES];     // vetor que guarda pessoas físicas (PF)
PessoaJuridica listaPJ[MAX_CLIENTES];   // vetor que guarda pessoas jurídicas (PJ)

// Contadores de quantas PF e PJ existem
int totalPF = 0;
int totalPJ = 0;

// Função para validar CPF
// Esta função verifica se um CPF é válido usando as regras da Receita Federal.
// Primeiro checa tamanho, depois dígitos repetidos e depois calcula os dígitos verificadores.
int validarCPF(char CPF[])
{
    int i;
    int quantidadeDigitos = 0;
    int primeiroDigito = 0;
    int segundoDigito = 0;
    char apenasNumeros[12];

    // Extraindo somente os números do CPF
    for(i = 0; CPF[i] != '\0'; i++)
    {
        if(CPF[i] >= '0' && CPF[i] <= '9')
        {
            apenasNumeros[quantidadeDigitos] = CPF[i];
            quantidadeDigitos++;
        }
    }
    apenasNumeros[quantidadeDigitos] = '\0';

    // CPF precisa ter exatamente 11 dígitos númericos
    if(quantidadeDigitos != 11)
    {
        return 0;
    }

    // verificando se todos os números são iguais
    int todosIguais = 1;
    for(i = 1; i < 11; i++)
    {
        if(apenasNumeros[i] != apenasNumeros[0])
        {
            todosIguais = 0;
            break;
        }
    }

    if(todosIguais == 1)
    {
        return 0;   // ex: 111.111.111-11
    }

    // calculando primeiro dígito verificador do CPF
    int peso = 10;
    for(i = 0; i < 9; i++)
    {
        primeiroDigito += (apenasNumeros[i] - '0') * peso;
        peso--;
    }

    primeiroDigito = (primeiroDigito * 10) % 11;
    if(primeiroDigito == 10)
    {
        primeiroDigito = 0;
    }

    // calculando segundo dígito verificador do CPF
    peso = 11;
    for(i = 0; i < 10; i++)
    {
        segundoDigito += (apenasNumeros[i] - '0') * peso;
        peso--;
    }

    segundoDigito = (segundoDigito * 10) % 11;
    if(segundoDigito == 10)
    {
        segundoDigito = 0;
    }

    // comparando com os dígitos originais do CPF
    if(primeiroDigito == (apenasNumeros[9] - '0') && segundoDigito == (apenasNumeros[10] - '0'))
    {
        return 1;   // válido
    }

    return 0;       // inválido
}

// Função para validar CNPJ
// Esta função verifica se um CNPJ é válido usando as regras da Receita Federal.
// Primeiro checa tamanho, depois dígitos repetidos e depois calcula os dígitos verificadores.
int validarCNPJ(char CNPJ[])
{
    int i;
    int quantidadeDigitos = 0;
    char apenasNumeros[15];

    // extraindo somente os números
    for(i = 0; CNPJ[i] != '\0'; i++)
    {
        if(CNPJ[i] >= '0' && CNPJ[i] <= '9')
        {
            apenasNumeros[quantidadeDigitos] = CNPJ[i];
            quantidadeDigitos++;
        }
    }
    apenasNumeros[quantidadeDigitos] = '\0';

    if(quantidadeDigitos != 14)
    {
        return 0;   // CNPJ deve ter 14 números
    }

    // verificando se todos são iguais
    int todosIguais = 1;
    for(i = 1; i < 14; i++)
    {
        if(apenasNumeros[i] != apenasNumeros[0])
        {
            todosIguais = 0;
            break;
        }
    }

    if(todosIguais == 1)
    {
        return 0;
    }

    // pesos usados no cálculo oficial
    int pesosPrimeiroDigito[12] = {5,4,3,2,9,8,7,6,5,4,3,2};
    int pesosSegundoDigito[13] = {6,5,4,3,2,9,8,7,6,5,4,3,2};

    int soma = 0;

    // calculando o primeiro dígito verificador do CNPJ
    for(i = 0; i < 12; i++)
    {
        soma += (apenasNumeros[i] - '0') * pesosPrimeiroDigito[i];
    }

    int primeiroDigito = soma % 11;
    primeiroDigito = (primeiroDigito < 2) ? 0 : (11 - primeiroDigito);

    // calculando o segundo dígito verificador do CNPJ
    soma = 0;
    for(i = 0; i < 13; i++)
    {
        soma += (apenasNumeros[i] - '0') * pesosSegundoDigito[i];
    }

    int segundoDigito = soma % 11;
    segundoDigito = (segundoDigito < 2) ? 0 : (11 - segundoDigito);

    // comparando com os dígitos originais do CNPJ
    if(primeiroDigito == (apenasNumeros[12] - '0') &&
       segundoDigito == (apenasNumeros[13] - '0'))
    {
        return 1;   // válido
    }

    return 0;       // inválido
}

// Função para cadastrar cliente (PF ou PJ)
void cadastrarCliente()
{
    char tipo;

    printf("\n==== CADASTRAR CLIENTE ====\n");
    printf("Cliente é Pessoa Física (F) ou Jurídica (J)? ");
    scanf(" %c", &tipo);

    // se for pessoa física
    if (tipo == 'F' || tipo == 'f') 
    {
        PessoaFisica novo; // cria uma nova PF
        novo.base.tipo = 'F'; // marca como PF

        printf("Digite o ID: ");
        scanf("%d", &novo.base.id);

        printf("Digite o nome: ");
        scanf(" %s", novo.nome);

        printf("Digite o CPF (somente números): ");
        scanf(" %s", novo.cpf);

        // valida CPF antes de aceitar
        if (!validarCPF(novo.cpf)) 
        {
            printf("CPF inválido! Cadastro cancelado.\n");
            return;
        }

        printf("Digite o endereço: ");
        scanf("%s", novo.base.endereco);

        printf("Digite o telefone fixo: ");
        scanf("%s", novo.base.telefone);

        printf("Digite o celular: ");
        scanf("%s", novo.celular);

        printf("Digite o e-mail: ");
        scanf("%s", novo.base.email);

        // adiciona no vetor
        listaPF[totalPF] = novo;
        totalPF++;

        printf("\nPessoa Física cadastrada com sucesso!\n");
    }

    // se for pessoa jurídica
    else if (tipo == 'J' || tipo == 'j') 
    {
        PessoaJuridica novo;
        novo.base.tipo = 'J';

        printf("Digite o ID: ");
        scanf("%d", &novo.base.id);

        printf("Digite a Razão Social: ");
        scanf("%s", novo.razaoSocial);

        printf("Digite o CNPJ (somente números): ");
        scanf("%s", novo.cnpj);

        if (!validarCNPJ(novo.cnpj)) 
        {
            printf("CNPJ inválido! Cadastro cancelado.\n");
            return;
        }

        printf("Digite o nome do contato da empresa: ");
        scanf("%s", novo.nomeContato);

        printf("Digite o endereço: ");
        scanf("%s", novo.base.endereco);

        printf("Digite o telefone fixo: ");
        scanf("%s", novo.base.telefone);

        printf("Digite o email: ");
        scanf("%s", novo.base.email);

        // adiciona no vetor
        listaPJ[totalPJ] = novo;
        totalPJ++;

        printf("\nPessoa Jurídica cadastrada com sucesso!\n");
    }
    else 
    {  
        printf("Tipo inválido! Use F ou J.\n");
    }
}