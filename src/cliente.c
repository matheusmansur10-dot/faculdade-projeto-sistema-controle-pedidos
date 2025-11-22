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

    // Verificando se todos os números são iguais
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

    // Calculando primeiro dígito verificador do CPF
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

    // Calculando segundo dígito verificador do CPF
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

    // Comparando com os dígitos originais do CPF
    if(primeiroDigito == (apenasNumeros[9] - '0') &&
       segundoDigito == (apenasNumeros[10] - '0'))
    {
        return 1;   // válido
    }

    return 0;       // inválido
}


int validarCNPJ(char CNPJ[])
{
    int i;
    int quantidadeDigitos = 0;
    char apenasNumeros[15];

    //Extraindo somente os números
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

    // Verificando se todos são iguais
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

    // Pesos usados no cálculo oficial
    int pesosPrimeiroDigito[12] = {5,4,3,2,9,8,7,6,5,4,3,2};
    int pesosSegundoDigito[13] = {6,5,4,3,2,9,8,7,6,5,4,3,2};

    int soma = 0;

    // Calculando o primeiro dígito verificador do CNPJ
    for(i = 0; i < 12; i++)
    {
        soma += (apenasNumeros[i] - '0') * pesosPrimeiroDigito[i];
    }

    int primeiroDigito = soma % 11;
    primeiroDigito = (primeiroDigito < 2) ? 0 : (11 - primeiroDigito);

    // Calculando o segundo dígito verificador do CNPJ
    soma = 0;
    for(i = 0; i < 13; i++)
    {
        soma += (apenasNumeros[i] - '0') * pesosSegundoDigito[i];
    }

    int segundoDigito = soma % 11;
    segundoDigito = (segundoDigito < 2) ? 0 : (11 - segundoDigito);

    // Comparando com os dígitos originais do CNPJ
    if(primeiroDigito == (apenasNumeros[12] - '0') &&
       segundoDigito == (apenasNumeros[13] - '0'))
    {
        return 1;   // válido
    }

    return 0;       // inválido
}