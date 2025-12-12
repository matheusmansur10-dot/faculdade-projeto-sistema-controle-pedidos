#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_CLIENTES 100

// --- Estruturas ---
typedef struct {
    int id;
    char tipo; // 'F' ou 'J'
    char endereco[100];
    char telefone[20];
    char email[50];
} ClienteBase;

typedef struct {
    ClienteBase base;
    char nome[100];
    char cpf[15];
} PessoaFisica;

typedef struct {
    ClienteBase base;
    char razaoSocial[100];
    char cnpj[20];
    char nomeContato[50];
} PessoaJuridica;

// --- Funções ---
void cadastrarCliente();
void consultarCliente();
void removerCliente();
void listarClientes();

// validações
int validarCPF(char *cpf);
int validarCNPJ(char *cnpj);


extern PessoaFisica listaPF[MAX_CLIENTES];
extern PessoaJuridica listaPJ[MAX_CLIENTES];
extern int totalPF;
extern int totalPJ;

#endif