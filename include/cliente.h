#ifndef CLIENTE_H
#define CLIENTE_H

// Classificar o tipo de cliente 
typedef enum 
{
    PESSOA_FISICA,          // PF
    PESSOA_JURIDICA         // PJ
} TipoCliente;

// Dados de pessoa física
typedef struct 
{
    char CPF[15];           // Ex: "000.000.000-00"
} DadosPessoaFisica;

// Dados de pessoa jurídica
typedef struct
{
    char CNPJ[20];          // Ex: "00.000.000/0000-00"
    char razao_social[100]; // Nome oficial da empresa
} DadosPessoaJuridica;

typedef struct 
{
    int id;                // identificação do cliente
    TipoCliente tipo;      // campo para armazenar se é PF ou PJ
    char nome[100];        // nome do cliente 
    char endereco[200];    // endereço do cliente
    char telefone[20];     // telefone do cliente
} Cliente;

// Armazenar somente os dados exclusivos(PF ou PJ)
union 
{
    DadosPessoaFisica PF;   // Armazena os dados exclusivos de pessoa física
    DadosPessoaJuridica PJ; // Armazena os dados exclusivos de pessoa jurídica
} DadosTipoCliente;


#endif // CLIENTE_H
