#include <ncurses.h> // Para desenhar na tela e ler o teclado
#include <string.h>  // Para copiar textos (strcpy)
#include "pedido.h"  // O "cardápio" deste módulo
#include "cliente.h"
#include "produto.h"

// --- Armazenamento de Dados ---
#define MAX_PEDIDOS 100
static Pedido lista_pedidos[MAX_PEDIDOS];
static int num_pedidos = 0;

// --- Função Auxiliar (Item 28) ---
int analisarPedido(int id)
{
    for (int i = 0; i < num_pedidos; i++)
    {
        if (lista_pedidos[i].id == id)
        {
            return 1; // Encontrou
        }
    }
    return 0; // Não encontrou
}
// --- Função Auxiliar para verificar se Cliente existe ---
// Retorna 1 se existe, 0 se não existe.
int clienteExiste(int id)
{
    // 1. Procura na lista de Pessoa Física
    for (int i = 0; i < totalPF; i++)
    {
        // Note que o ID está dentro de 'base'
        if (listaPF[i].base.id == id)
        {
            return 1; // Encontrou em PF
        }
    }

    // 2. Procura na lista de Pessoa Jurídica
    for (int i = 0; i < totalPJ; i++)
    {
        if (listaPJ[i].base.id == id)
        {
            return 1; // Encontrou em PJ
        }
    }

    return 0; // Não encontrou em lugar nenhum
}

// --- Função Principal de Cadastro (Item 29) ---
void inserirPedido()
{
    int id_temp, cliente_temp;
    char data_temp[11];

    // 1. Prepara a tela
    clear();           // Limpa a tela do terminal
    box(stdscr, 0, 0); // Desenha uma borda bonita
    mvprintw(1, 2, "=== CADASTRAR NOVO PEDIDO ===");

    // 2. Pede o ID do Pedido
    mvprintw(3, 2, "Digite o ID do Pedido: ");
    echo();                // Habilita aparecer o que você digita
    scanw("%d", &id_temp); // Lê o número digitado

    // 3. Verifica se o ID já existe (Usa sua função do Item 28!)
    if (analisarPedido(id_temp) == 1)
    {
        attron(A_BOLD); // Negrito
        mvprintw(5, 2, "ERRO: Esse ID ja existe no sistema!");
        attroff(A_BOLD);
        mvprintw(7, 2, "Pressione qualquer tecla para voltar...");
        noecho(); // Desabilita o echo
        getch();  // Espera
        return;   // Cancela e volta para o menu
    }

    // 4. Pede o ID do Cliente
    mvprintw(4, 2, "Digite o ID do Cliente: ");
    scanw("%d", &cliente_temp);
    if (clienteExiste(cliente_temp) == 0)
    {
        attron(A_BOLD);
        mvprintw(6, 2, "ERRO: Cliente ID %d nao encontrado!", cliente_temp);
        attroff(A_BOLD);
        mvprintw(8, 2, "Dica: Cadastre o cliente no modulo de Clientes.");
        mvprintw(10, 2, "Pressione qualquer tecla para voltar...");
        noecho();
        getch();
        return; // Cancela e volta
    }

    // 5. Pede a Data
    mvprintw(5, 2, "Data (dd/mm/aaaa): ");
    scanw("%s", data_temp);

    // 6. Salvar os dados no Array (Persistência em Memória)
    if (num_pedidos < MAX_PEDIDOS)
    {
        lista_pedidos[num_pedidos].id = id_temp;
        lista_pedidos[num_pedidos].clienteId = cliente_temp;
        strcpy(lista_pedidos[num_pedidos].data, data_temp); // Copia a data
        lista_pedidos[num_pedidos].total = 0.0;             // Começa com zero

        num_pedidos++; // Aumenta o contador de pedidos

        mvprintw(7, 2, "Sucesso! Pedido cadastrado.");
    }
    else
    {
        mvprintw(7, 2, "Erro: Lista de pedidos cheia!");
    }

    // 7. Finalização
    mvprintw(9, 2, "Pressione qualquer tecla para voltar...");
    noecho(); // Esconde o cursor de novo para o menu ficar bonito
    getch();  // Espera o usuário ler
}
// --- Função de Consulta (Item 30) ---
void consultarPedido()
{
    int id_busca;
    int encontrado = 0;

    // 1. Prepara a tela
    clear();
    box(stdscr, 0, 0);
    mvprintw(1, 2, "=== CONSULTAR PEDIDO ===");

    // 2. Pede o ID
    mvprintw(3, 2, "Digite o ID do Pedido para buscar: ");
    echo();
    scanw("%d", &id_busca);
    noecho();

    // 3. Procura na lista
    for (int i = 0; i < num_pedidos; i++)
    {
        if (lista_pedidos[i].id == id_busca)
        {
            // ACHOU! Mostra os dados
            attron(A_BOLD);
            mvprintw(5, 2, "--- PEDIDO ENCONTRADO ---");
            attroff(A_BOLD);

            mvprintw(7, 4, "ID do Pedido:  %d", lista_pedidos[i].id);
            mvprintw(8, 4, "ID do Cliente: %d", lista_pedidos[i].clienteId);
            mvprintw(9, 4, "Data:          %s", lista_pedidos[i].data);
            mvprintw(10, 4, "Total:         R$ %.2f", lista_pedidos[i].total);

            encontrado = 1;
            break;
        }
    }

    // 4. Se não achou
    if (encontrado == 0)
    {
        attron(A_BOLD);
        mvprintw(6, 2, "ERRO: Pedido com ID %d nao encontrado!", id_busca);
        attroff(A_BOLD);
    }

    // 5. Finalização
    mvprintw(12, 2, "Pressione qualquer tecla para voltar...");
    getch();
}
// --- Função de Listagem (Item 31) ---
void listarPedidos()
{
    // 1. Prepara a tela
    clear();
    box(stdscr, 0, 0);
    mvprintw(1, 2, "=== LISTA DE PEDIDOS ===");

    // 2. Verifica se está vazio
    if (num_pedidos == 0)
    {
        mvprintw(3, 2, "Nenhum pedido cadastrado no sistema.");
    }
    else
    {
        // 3. Cabeçalho da Tabela
        attron(A_BOLD);
        mvprintw(3, 2, "ID   | CLIENTE  | DATA        | TOTAL");
        mvprintw(4, 2, "------------------------------------------");
        attroff(A_BOLD);

        // 4. Loop para mostrar cada pedido
        for (int i = 0; i < num_pedidos; i++)
        {
            mvprintw(5 + i, 2, "%-4d | %-8d | %-11s | R$ %.2f",
                     lista_pedidos[i].id,
                     lista_pedidos[i].clienteId,
                     lista_pedidos[i].data,
                     lista_pedidos[i].total);
        }
    }

    // 5. Finalização
    mvprintw(LINES - 2, 2, "Pressione qualquer tecla para voltar...");
    getch();
}
// --- Função de Remoção (Item 32) ---
void removerPedido()
{
    int id_busca;
    int encontrado = 0;
    char confirmacao;

    // 1. Prepara a tela
    clear();
    box(stdscr, 0, 0);
    mvprintw(1, 2, "=== REMOVER PEDIDO ===");

    // 2. Pede o ID
    mvprintw(3, 2, "Digite o ID do Pedido para EXCLUIR: ");
    echo();
    scanw("%d", &id_busca);
    noecho();

    // 3. Procura na lista
    for (int i = 0; i < num_pedidos; i++)
    {
        if (lista_pedidos[i].id == id_busca)
        {
            encontrado = 1;

            // Mostra o que vai ser apagado para confirmar
            mvprintw(5, 2, "Encontrado: Cliente %d | Total R$ %.2f",
                     lista_pedidos[i].clienteId, lista_pedidos[i].total);

            mvprintw(7, 2, "Tem certeza? (s/n): ");
            echo();
            scanw(" %c", &confirmacao); // O espaço antes do %c é importante!
            noecho();

            if (confirmacao == 's' || confirmacao == 'S')
            {
                // --- O PULO DO GATO: REMOÇÃO COM SHIFT ---
                // Move todos os pedidos da frente uma casa para trás
                for (int j = i; j < num_pedidos - 1; j++)
                {
                    lista_pedidos[j] = lista_pedidos[j + 1];
                }

                num_pedidos--; // Diminui o tamanho da lista

                attron(A_BOLD);
                mvprintw(9, 2, "Sucesso! Pedido removido.");
                attroff(A_BOLD);
            }
            else
            {
                mvprintw(9, 2, "Operacao cancelada.");
            }
            break; // Sai do loop de busca
        }
    }

    if (encontrado == 0)
    {
        attron(A_BOLD);
        mvprintw(5, 2, "ERRO: Pedido ID %d nao encontrado.", id_busca);
        attroff(A_BOLD);
    }

    mvprintw(11, 2, "Pressione qualquer tecla para voltar...");
    getch();
}
void salvarPedidos()
{
    FILE *arquivo = fopen("pedidos.csv", "w"); // "w" = Write (Escrever Texto)

    if (arquivo == NULL)
    {
        mvprintw(LINES - 2, 2, "Erro ao salvar pedidos.csv!");
        getch();
        return;
    }

    // Opcional: Escrever um cabeçalho na primeira linha
    fprintf(arquivo, "ID,ClienteID,Data,Total\n");

    // Loop para salvar cada pedido, linha por linha
    for (int i = 0; i < num_pedidos; i++)
    {
        fprintf(arquivo, "%d,%d,%s,%.2f\n",
                lista_pedidos[i].id,
                lista_pedidos[i].clienteId,
                lista_pedidos[i].data,
                lista_pedidos[i].total);
    }

    fclose(arquivo);
}

void carregarPedidos()
{
    FILE *arquivo = fopen("pedidos.csv", "r"); // "r" = Read (Ler Texto)

    if (arquivo == NULL)
    {
        num_pedidos = 0; // Arquivo não existe? Começa do zero.
        return;
    }

    // Variável lixo para pular o cabeçalho (se tiver)
    char buffer[100];
    fscanf(arquivo, "%s\n", buffer); // Lê a primeira linha (cabeçalho) e descarta

    // Loop de Leitura
    num_pedidos = 0;
    while (num_pedidos < MAX_PEDIDOS)
    {
        // Tenta ler 4 campos separados por vírgula
        // O formato "%d,%d,%[^,],%lf" significa: Int, Int, String(até a vírgula), Double
        int leu = fscanf(arquivo, "%d,%d,%[^,],%lf\n",
                         &lista_pedidos[num_pedidos].id,
                         &lista_pedidos[num_pedidos].clienteId,
                         lista_pedidos[num_pedidos].data,
                         &lista_pedidos[num_pedidos].total);

        if (leu == 4)
        { // Se conseguiu ler os 4 campos com sucesso
            num_pedidos++;
        }
        else
        {
            break; // Se não leu 4 coisas, provavelmente acabou o arquivo
        }
    }

    fclose(arquivo);
}