#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "cliente.h"
#include "persistencia.h" // Importante: É aqui que está a mágica de salvar no CSV

// Vetores globais para armazenar os clientes em memória RAM enquanto o programa roda
PessoaFisica listaPF[MAX_CLIENTES];
PessoaJuridica listaPJ[MAX_CLIENTES];
int totalPF = 0;
int totalPJ = 0;

/*
 * Função: validarCPF
 * -------------------
 * Objetivo: Verifica se o CPF digitado é matematicamente válido segundo as regras da Receita Federal.
 * * Como funciona:
 * 1. Remove qualquer caractere que não seja número (pontos, traços).
 * 2. Verifica se todos os dígitos são iguais (ex: 111.111.111-11), o que é inválido.
 * 3. Calcula os dois "Dígitos Verificadores" (os dois últimos números do CPF) usando
 * a lógica de Módulo 11 (multiplicação por pesos 10, 9, 8... e resto da divisão).
 * * Retorno: 1 se for Válido, 0 se for Inválido.
 */
int validarCPF(char *cpf) {
    int i, j, digito1 = 0, digito2 = 0;
    char cpf_limpo[12];
    int len = strlen(cpf);
    int k = 0;

    // Passo 1: Limpeza (Extrai apenas os números)
    for(i=0; i<len; i++) {
        if(isdigit(cpf[i])) {
            cpf_limpo[k++] = cpf[i];
        }
    }
    cpf_limpo[k] = '\0'; // Finaliza a string

    // Passo 2: Verificações básicas
    if(strlen(cpf_limpo) != 11) return 0; // CPF deve ter 11 dígitos

    // Checa sequências iguais (inválidas)
    if(strcmp(cpf_limpo, "00000000000") == 0 || strcmp(cpf_limpo, "11111111111") == 0 ||
       strcmp(cpf_limpo, "22222222222") == 0 || strcmp(cpf_limpo, "33333333333") == 0 ||
       strcmp(cpf_limpo, "44444444444") == 0 || strcmp(cpf_limpo, "55555555555") == 0 ||
       strcmp(cpf_limpo, "66666666666") == 0 || strcmp(cpf_limpo, "77777777777") == 0 ||
       strcmp(cpf_limpo, "88888888888") == 0 || strcmp(cpf_limpo, "99999999999") == 0)
        return 0;

    // Passo 3: Cálculo do 1º Dígito Verificador
    for(i = 0, j = 10; i < 9; i++, j--) {
        digito1 += (cpf_limpo[i] - '0') * j;
    }
    digito1 %= 11;
    if(digito1 < 2) digito1 = 0;
    else digito1 = 11 - digito1;

    if((cpf_limpo[9] - '0') != digito1) return 0; // Se não bater, é inválido

    // Passo 4: Cálculo do 2º Dígito Verificador
    for(i = 0, j = 11; i < 10; i++, j--) {
        digito2 += (cpf_limpo[i] - '0') * j;
    }
    digito2 %= 11;
    if(digito2 < 2) digito2 = 0;
    else digito2 = 11 - digito2;

    if((cpf_limpo[10] - '0') != digito2) return 0; // Se não bater, é inválido

    return 1; // Se passou por tudo, o CPF é matemático e válido!
}

// Validação simples de CNPJ
int validarCNPJ(char *cnpj) {
    if(strlen(cnpj) < 14) return 0;
    return 1;
}

/*
 * Função: cadastrarCliente
 * ------------------------
 * Exibe o formulário de cadastro usando ncurses (interface gráfica).
 * Possui um LOOP DE VALIDAÇÃO que impede o usuário de avançar com CPF inválido.
 * Ao final, salva os dados no arquivo 'data/Clientes.csv' chamando o módulo de persistência.
 */
void cadastrarCliente()
{
    char tipo;
    
    // Configurações iniciais da janela gráfica
    echo();       // Habilita mostrar o que se digita
    curs_set(1);  // Mostra o cursor
    clear();      // Limpa a tela
    box(stdscr, 0, 0); // Desenha a borda

    mvprintw(1, 2, "=== CADASTRAR CLIENTE ===");
    mvprintw(3, 2, "Tipo (F = Fisica / J = Juridica): ");
    scanw(" %c", &tipo);

    if (tipo == 'F' || tipo == 'f') 
    {
        PessoaFisica novo;
        novo.base.tipo = 'F';

        mvprintw(5, 2, "ID do Cliente: ");
        scanw("%d", &novo.base.id);

        mvprintw(6, 2, "Nome Completo: ");
        scanw(" %[^\n]", novo.nome); 

        // --- LOOP DE INSISTÊNCIA (Validação de CPF) ---
        while(1) {
            move(7, 0); clrtoeol(); // Limpa a linha para não encavalar texto
            box(stdscr, 0, 0);      // Redesenha a borda caso tenha sido apagada
            mvprintw(7, 2, "CPF (apenas numeros): ");
            scanw(" %s", novo.cpf);
            
            // Chama a função matemática criada acima
            if(validarCPF(novo.cpf)) {
                mvprintw(7, 40, " [OK] "); 
                break; // CPF Válido: Sai do loop e continua o cadastro
            } else {
                // CPF Inválido: Avisa e repete o loop
                attron(A_BLINK); // Texto piscando para alertar
                mvprintw(7, 40, " INVALIDO! Tente novamente. ");
                attroff(A_BLINK);
                beep(); // Faz um som de alerta
            }
        }
        // ---------------------------------------------

        mvprintw(8, 2, "Endereco: ");
        scanw(" %[^\n]", novo.base.endereco);

        mvprintw(9, 2, "Telefone: ");
        scanw(" %s", novo.base.telefone);

        mvprintw(10, 2, "Email: ");
        scanw(" %s", novo.base.email);

        // 1. Salva na Memória RAM (para uso imediato)
        listaPF[totalPF] = novo;
        totalPF++;

        attron(A_BOLD); 
        mvprintw(12, 2, ">>> Pessoa Fisica cadastrada com sucesso! <<<");
        attroff(A_BOLD);
        
        // 2. Salva no Disco (Persistência no arquivo data/Clientes.csv)
        salvarClientesCSV();
    }
    else if (tipo == 'J' || tipo == 'j') 
    {
        PessoaJuridica novo;
        novo.base.tipo = 'J';

        mvprintw(5, 2, "ID do Cliente: ");
        scanw("%d", &novo.base.id);

        mvprintw(6, 2, "Razao Social: ");
        scanw(" %[^\n]", novo.razaoSocial);

        mvprintw(7, 2, "CNPJ: ");
        scanw(" %s", novo.cnpj);

        mvprintw(8, 2, "Nome Contato: ");
        scanw(" %[^\n]", novo.nomeContato);

        mvprintw(9, 2, "Endereco: ");
        scanw(" %[^\n]", novo.base.endereco);

        mvprintw(10, 2, "Telefone: ");
        scanw(" %s", novo.base.telefone);

        mvprintw(11, 2, "Email: ");
        scanw(" %s", novo.base.email);
        
        // Salva na Memória
        listaPJ[totalPJ] = novo;
        totalPJ++;
        
        attron(A_BOLD);
        mvprintw(13, 2, ">>> PJ cadastrada com sucesso! <<<");
        attroff(A_BOLD);
        
        // Salva no Disco
        salvarClientesCSV();
    }
    else {
        mvprintw(5, 2, "Opcao invalida!");
    }

    mvprintw(15, 2, "Pressione qualquer tecla para voltar...");
    noecho(); 
    curs_set(0); 
    getch();
}

/*
 * Função: consultarCliente
 * ------------------------
 * Busca um cliente pelo ID nos vetores carregados.
 */
void consultarCliente()
{
    int id;
    echo(); curs_set(1);
    clear(); box(stdscr, 0, 0);

    mvprintw(1, 2, "=== CONSULTAR CLIENTE ===");
    mvprintw(3, 2, "Digite o ID para buscar: ");
    scanw("%d", &id);
    
    noecho(); curs_set(0);

    int achou = 0;
    // Busca sequencial no vetor de PF
    for (int i = 0; i < totalPF; i++) {
        if (listaPF[i].base.id == id) {
            mvprintw(5, 2, "[Pessoa Fisica Encontrada]");
            mvprintw(7, 2, "Nome: %s", listaPF[i].nome);
            mvprintw(8, 2, "CPF:  %s", listaPF[i].cpf);
            mvprintw(9, 2, "Email: %s", listaPF[i].base.email);
            achou = 1;
            break;
        }
    }
    
    // Se não achou em PF, busca no vetor de PJ
    if (!achou) {
        for (int i = 0; i < totalPJ; i++) {
            if (listaPJ[i].base.id == id) {
                mvprintw(5, 2, "[Pessoa Juridica Encontrada]");
                mvprintw(7, 2, "Razao: %s", listaPJ[i].razaoSocial);
                mvprintw(8, 2, "CNPJ:  %s", listaPJ[i].cnpj);
                achou = 1;
                break;
            }
        }
    }

    if (!achou) mvprintw(5, 2, "Cliente nao encontrado.");

    mvprintw(12, 2, "Pressione qualquer tecla para voltar...");
    getch();
}

/*
 * Função: removerCliente
 * ----------------------
 * Remove um cliente pelo ID e atualiza o arquivo CSV imediatamente.
 */
void removerCliente()
{
    int id;
    echo(); curs_set(1);
    clear(); box(stdscr, 0, 0);

    mvprintw(1, 2, "=== REMOVER CLIENTE ===");
    mvprintw(3, 2, "Digite o ID para remover: ");
    scanw("%d", &id);
    
    noecho(); curs_set(0);

    // Tenta remover de PF
    for (int i = 0; i < totalPF; i++) {
        if (listaPF[i].base.id == id) {
            // "Puxa" todos os elementos da frente para trás (tapa o buraco)
            for (int j = i; j < totalPF - 1; j++) listaPF[j] = listaPF[j+1];
            totalPF--; // Diminui o tamanho da lista
            
            mvprintw(5, 2, "Sucesso! Pessoa Fisica removida.");
            salvarClientesCSV(); // Atualiza o arquivo data/Clientes.csv
            getch(); 
            return;
        }
    }

    // Tenta remover de PJ
    for (int i = 0; i < totalPJ; i++) {
        if (listaPJ[i].base.id == id) {
            for (int j = i; j < totalPJ - 1; j++) listaPJ[j] = listaPJ[j+1];
            totalPJ--;
            
            mvprintw(5, 2, "Sucesso! Pessoa Juridica removida.");
            salvarClientesCSV(); // Atualiza o arquivo data/Clientes.csv
            getch(); 
            return;
        }
    }

    mvprintw(5, 2, "Cliente nao encontrado.");
    getch();
}

// Lista todos os clientes na tela
void listarClientes()
{
    clear(); box(stdscr, 0, 0);
    mvprintw(1, 2, "=== LISTA GERAL DE CLIENTES ===");
    
    int l = 3;
    
    attron(A_UNDERLINE);
    mvprintw(l++, 2, "PESSOAS FISICAS:");
    attroff(A_UNDERLINE);
    
    for (int i = 0; i < totalPF; i++) {
        mvprintw(l++, 4, "ID: %d | %s | %s", listaPF[i].base.id, listaPF[i].nome, listaPF[i].cpf);
    }
    if (totalPF == 0) mvprintw(l++, 4, "(Nenhum)");

    l++;
    attron(A_UNDERLINE);
    mvprintw(l++, 2, "PESSOAS JURIDICAS:");
    attroff(A_UNDERLINE);

    for (int i = 0; i < totalPJ; i++) {
        mvprintw(l++, 4, "ID: %d | %s | %s", listaPJ[i].base.id, listaPJ[i].razaoSocial, listaPJ[i].cnpj);
    }
    if (totalPJ == 0) mvprintw(l++, 4, "(Nenhum)");

    mvprintw(l + 2, 2, "Pressione qualquer tecla para voltar...");
    getch();
}