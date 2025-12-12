#ifndef CLIENTE_H
#define CLIENTE_H
// Tamanho máximo das listas
#define MAX_CLIENTES 200

// Struct Cliente (usado tanto por PF quanto PJ)
typedef struct {
    int id;             // id do cliente 
    char endereco[200]; // endereço do cliente 
    char telefone[20];  // telefone do cliente
    char email[100];    // email do cliente 
    char tipo;          // tipo do cliente 'F' = física, 'J' = jurídica
} Cliente;

// Struct Pessoa Física
typedef struct {
    Cliente base;       // aqui é como se "herdasse" os dados de Cliente
    char nome[100];     // nome do cliente 
    char celular[20];   // telefone do cliente 
    char cpf[15];       // ex: 000.000.000-00
} PessoaFisica;

// Struct Pessoa Jurídica
typedef struct {
    Cliente base;           // aqui é como se "herdasse" os dados de Cliente
    char razaoSocial[100];  // nome oficial da empresa 
    char nomeContato[100];  // nome de quem responde pela empresa
    char cnpj[20];          // ex: 00.000.000/0000-00
} PessoaJuridica;

// Listas de clientes (vetores)
extern PessoaFisica listaPF[MAX_CLIENTES];      // lista de pessoas físicas
extern PessoaJuridica listaPJ[MAX_CLIENTES];    // lista de pessoas jurídicas
extern int totalPF;                             // quantidade atual de PF cadastradas
extern int totalPJ;                             // quantidade atual de PJ cadastradas

// Protótipos das funções
void cadastrarCliente();        // cadastra PF ou PJ
void consultarCliente();        // pesquisa cliente usando ID
void removerCliente();          // remove cliente usando ID
void listarClientes();          // lista todos os clientes cadastrados

int validarCPF(char cpf[]);     // valida CPF seguindo a Receita Federal
int validarCNPJ(char cnpj[]);   // valida CNPJ seguindo a Receita Federal

void salvarClientesCSV();
void carregarClientes();       // salva clientes no arquivo CSV

#endif // CLIENTE_H