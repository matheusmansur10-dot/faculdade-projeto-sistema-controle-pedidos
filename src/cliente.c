void menuCliente()
{
    int opcao = -1;

    while (opcao != 0)
    {
        printf("\n==============================\n");
        printf("         MENU CLIENTES        \n");
        printf("==============================\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Consultar Cliente\n");
        printf("3 - Remover Cliente\n");
        printf("4 - Listar Clientes\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if(opcao == 1)
        {
            // cadastrarCliente();
        }
        else if(opcao == 2)
        {
            // consultarCliente();
        }
        else if(opcao == 3)
        {
            // removerCliente();
        }
        else if(opcao == 4)
        {
            // listarClientes();
        }
        else if(opcao != 0)
        {
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    }
}