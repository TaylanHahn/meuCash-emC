/******************************************************************************
APP MEU CASH 

� um programa de controle financeiro simples que permite registrar ganhos e gastos fixos, ganhos e gastos eventuais e exibir o saldo atual. Com o objetivo de tornar o controle financeiro mais eficiente e informativo para quem utiliza o app. Ele roda localmente, sem precisar de internet para funcionar, basta copiar o arquivo para o desktop e executar. 
*******************************************************************************/

// Inclui as bibliotecas necess�rias
#include <stdio.h> 
#include <stdlib.h>
#include <locale.h>

// Declara��o das fun��es que ser�o utilizadas no programa
void registrarGanhosFixos();
void registrarSaidasFixas();
void registrarGanhosEventuais();
void registrarSaidasEventuais();
void atualizarSaldo();
void exibirExtrato();
void registrarTransacao(float valor, const char* tipo, const char* natureza);
void exibirMenu();
void calculadoraSimples();
void previsaoInvestimento();
void salvarDados();       
void carregarDados(); 
void formatarDados();


// Declara��o das vari�veis globais
float ganhosFixos=0.0, saidasFixas=0.0, ganhosEventuais=0.0, saidasEventuais=0.0, saldo=0.0;

// Declara��o da estrutura para armazenar as transa��es
#define MAX_TRANSACOES 50
typedef struct {
    float valor;
    char tipo[10];     // "Fixa" ou "Eventual"
    char natureza[10]; // "Entrada" ou "Sa�da"
} Transacao;

Transacao transacoes[MAX_TRANSACOES];
int totalTransacoes = 0;


// Fun��o principal (main)
int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil"); // Configura o locale para Portug�s, arrumando os acentos
    carregarDados(); // Carrega os dados do arquivo .txt ao iniciar

    // In�cio da exibi��o do cabe�alho e do menu 
    printf("\tBem-vindo ao MeuCASH\n");
    printf("\tO app ideal para o seu controle financeiro\n");

    int opcao;
    do {
        // Exibe o menu de op��es
        printf("---------------------------------------------------------------------\n");
        printf("\n\t~~~ Escolha uma fun��o ~~~\n");
        printf("\t(Digite apenas o n�mero da op��o desejada)\n\n");
        printf("\t1 - Registrar ganhos fixos\n");
        printf("\t2 - Registrar gastos fixos\n");
        printf("\t3 - Registrar ganhos eventuais\n");
        printf("\t4 - Registrar gastos eventuais\n");
        printf("\t5 - Exibir saldo atual\n");
        printf("\t6 - Exibir extrato\n");
        printf("\n\t~~~ Fun��es extras ~~~\n\n");
        printf("\t7 - Calculadora simples\n");
        printf("\t8 - Calcular previs�o de investimentos\n");
        printf("\n\t~~~ Encerrar opera��es ~~~\n\n");
        printf("\t9 - Formatar todos os dados\n");
        printf("\t10 - Salvar e Sair\n");
        printf("\t11 - Sair\n\n");
        printf("---------------------------------------------------------------------\n");
        scanf("%d", &opcao);
        system("cls"); // Limpa a tela
        
        // Switch para executar a op��o escolhida, sendo chamada a fun��o referenciada.
        switch(opcao){
            case 1: registrarGanhosFixos(); break;
            case 2: registrarSaidasFixas(); break;
            case 3: registrarGanhosEventuais(); break;
            case 4: registrarSaidasEventuais(); break;
            case 5: printf("\nSeu saldo atual � de R$ %.2f\n", saldo); break;
            case 6: exibirExtrato(); break;
            case 7: calculadoraSimples(); break;
            case 8: previsaoInvestimento(); break;
            case 9: formatarDados(); break;
            case 10: salvarDados(); printf("\nSalvando e saindo do app...\n"); break;
            case 11: printf("\nSaindo do aplicativo...\n"); break;
            default: printf("\nOp��o inv�lida,. Tente novamente.\n");
        }
    } while (opcao != 10 && opcao != 11);
    return 0;
}

    // ======================================== Fun��es de Registro ========================================
    // As fun��es de registro de ganhos e sa�das recebem o valor e o tipo de transa��o (Fixa ou Eventual).

    // Registro de GANHOS FIXOS
    void registrarGanhosFixos(){
        double valor; // Declara o valor
        printf("Informe o valor dos ganhos fixos: "); // Mensagem para o usu�rio
        scanf( "%lf", &valor); // Leitura do valor
        ganhosFixos += valor; // Adiciona o valor aos ganhos fixos
        atualizarSaldo(); // Atualiza o saldo
        salvarDados(); // Salva os dados
        registrarTransacao(valor, "Fixa", "Entrada"); // Registra a transa��o e o tipo, para ser exibido no extrato
    }
    
    // Registro de SA�DAS FIXAS
    void registrarSaidasFixas(){
        double valor;
        printf("Informe o valor das sa�das fixas: ");
        scanf( "%lf", &valor);
        saidasFixas += valor;
        atualizarSaldo();
        salvarDados();
        registrarTransacao(valor, "Fixa", "Saida");
    }
    // Registrar GANHOS EVENTUAIS
    void registrarGanhosEventuais(){
        double valor;
        printf("Informe o valor de ganhos eventuais: ");
        scanf( "%lf", &valor);
        ganhosEventuais += valor;
        atualizarSaldo();
        salvarDados();
        registrarTransacao(valor, "Eventual", "Entrada");
    }
    // Registrar SA�DAS EVENTUAIS
    void registrarSaidasEventuais(){
        double valor;
        printf("Informe o valor de sa�das eventuais: ");
        scanf( "%lf", &valor);
        saidasEventuais += valor;
        atualizarSaldo();
        salvarDados();
        registrarTransacao(valor, "Eventual", "Saida");
    }
    
    // Fun��o de ATUALIZAR SALDO 
    void atualizarSaldo(){
        saldo = ganhosFixos - saidasFixas + ganhosEventuais - saidasEventuais;
    }

    // Fun��o para REGISTRAR transa��es
    // Essa fun��o exibir� as 5 movimenta��es mais recentes no extrato e a natureza da transa��o (entrada ou sa�da). 
    void registrarTransacao(float valor, const char* tipo, const char* natureza) {
    if (totalTransacoes < MAX_TRANSACOES) {
        transacoes[totalTransacoes].valor = valor; // Insere o valor na transa��o
        snprintf(transacoes[totalTransacoes].tipo, sizeof(transacoes[totalTransacoes].tipo), "%s", tipo); // Insere o tipo na transa��o 
        snprintf(transacoes[totalTransacoes].natureza, sizeof(transacoes[totalTransacoes].natureza), "%s", natureza); // Insere a natureza na transa��o 
        totalTransacoes++; // Incrementa o total de transa��es
    } else {
        // Desloca tudo para tr�s e insere no fim a nova transa��o
        for (int i = 1; i < MAX_TRANSACOES; i++) {
            transacoes[i - 1] = transacoes[i];
        }
        transacoes[MAX_TRANSACOES - 1].valor = valor; 
        snprintf(transacoes[MAX_TRANSACOES - 1].tipo, sizeof(transacoes[MAX_TRANSACOES - 1].tipo), "%s", tipo);
        snprintf(transacoes[MAX_TRANSACOES - 1].natureza, sizeof(transacoes[MAX_TRANSACOES - 1].natureza), "%s", natureza); 
    }
}

    // =================================== Fun��es de Mem�ria ============================================== 
    // As fun��es de mem�ria carregam e salvam os dados em um arquivo texto. Caso o arquivo ainda nao exista, ele cria um novo na mesma pasta.

    // Fun��o para exibir o extrato
    void exibirExtrato() {
    int entradas = 0, saidas = 0;

    // Exibe as 5 transa��es mais recentes
    printf("\n�ltimas 5 Entradas:\n");
    for (int i = totalTransacoes - 1; i >= 0 && entradas < 5; i--) {
        if (strcmp(transacoes[i].natureza, "Entrada") == 0) {
            printf("Valor: R$ %.2f | Tipo: %s\n", transacoes[i].valor, transacoes[i].tipo);
            entradas++;
        }
    }

    printf("\n�ltimas 5 Sa�das:\n");
    for (int i = totalTransacoes - 1; i >= 0 && saidas < 5; i--) {
        if (strcmp(transacoes[i].natureza, "Saida") == 0) {
            printf("Valor: R$ %.2f | Tipo: %s\n", transacoes[i].valor, transacoes[i].tipo);
            saidas++;
        }
    }
}

    // Fun��o para salvar os dados em um arquivo texto
    void salvarDados() {
        FILE *arquivo = fopen("dados.txt", "w"); // Abre (ou cria) o arquivo no modo escrita
        if (arquivo == NULL) {
            printf("Erro ao salvar os dados!\n");
            return;
        }

        // Grava os valores no arquivo
        fprintf(arquivo, "%.2f %.2f %.2f %.2f %.2f\n", ganhosFixos, saidasFixas, ganhosEventuais, saidasEventuais, saldo);

        // Salva o n�mero de transa��es
        fprintf(arquivo, "%d\n", totalTransacoes);

        // Salva cada transa��o
        for (int i = 0; i < totalTransacoes; i++) {
            fprintf(arquivo, "%.2f %s %s\n", transacoes[i].valor, transacoes[i].tipo, transacoes[i].natureza);
        }

        fclose(arquivo); // Fecha o arquivo
        printf("\t\nDados salvos com sucesso!\n\n"); // Exibe uma mensagem de sucesso
    }

    // Fun��o para carregar os dados do arquivo (se existir)
    void carregarDados() {
        FILE *arquivo = fopen("dados.txt", "r"); // Abre o arquivo no modo leitura
        if (arquivo == NULL) {
            // Caso o arquivo ainda n�o exista, assume os valores padr�o (0.0)
            return;
        }

        // L� os valores gravados anteriormente
        fscanf(arquivo, "%f %f %f %f %f", &ganhosFixos, &saidasFixas, &ganhosEventuais, &saidasEventuais, &saldo);

        // L� o n�mero de transa��es
        fscanf(arquivo, "%d\n", &totalTransacoes);

        // L� as transa��es
        for (int i = 0; i < totalTransacoes; i++) {
            fscanf(arquivo, "%f %s %s\n", &transacoes[i].valor, transacoes[i].tipo, transacoes[i].natureza);
        }

        fclose(arquivo);
        atualizarSaldo();
        printf("\t\n\nDados carregados com sucesso!\n\n");  
    }

    // Fun��o para FORMATAR todos os dados
    void formatarDados() {
        ganhosFixos = 0.0;
        saidasFixas = 0.0;
        ganhosEventuais = 0.0;
        saidasEventuais = 0.0;
        saldo = 0.0;
        totalTransacoes = 0;

        for (int i = 0; i < MAX_TRANSACOES; i++) {
            transacoes[i].valor = 0.0;
            strcpy(transacoes[i].tipo, "");
            strcpy(transacoes[i].natureza, "");
        }

        salvarDados(); // Salva os dados zerados no arquivo
        printf("\t\nTodos os dados foram formatados com sucesso!\n\n");
    }


    // ============================================ Fun��es Extras =========================================
    // As fun��es extras foram criadas para melhorar a experiencia do usuario. Oferecem ferramentas adicionais e ajudam a tornar o app mais completo e eficiente, como a fun��o de CALCULADORA SIMPLES e a fun��o de CALCULAR PREVIS�O DE INVESTIMENTOS.

    // Fun��o CALCULADORA SIMPLES
    void calculadoraSimples(){
        // Declara��o das vari�veis
        float num1, num2, resultado;
        char operador;  

        printf("Informe o primeiro n�mero: "); 
        scanf("%f", &num1);

        printf("Insira apenas o s�mbolo do operador \n(+ para adi��o, - para subtra��o, * para multiplica��o, / para divis�o): "); // Leitura do operador
        scanf(" %c", &operador);

        printf("Informe o segundo n�mero: ");
        scanf("%f", &num2);

        // Realiza o c�lculo dependendo do operador
        if(operador == '+') {
            resultado = num1 + num2;
            printf("\nResultado: %.2f\n", resultado);
        } else if (operador == '-') {
            resultado = num1 - num2;
            printf("\nResultado: %.2f\n", resultado);
        } else if (operador == '*') {
            resultado = num1 * num2;
            printf("\nResultado: %.2f\n", resultado);
        } else if (operador == '/') {
            if (num2 != 0) {
                resultado = num1 / num2;
                printf("\nResultado: %.2f\n", resultado);
            } else {
                printf("\nErro: Divis�o por zero n�o permitida.\n");
            }
        } else {
            printf("\nOperador inv�lido.\n");
        }
    }


    // Fun��o para calcular previs�o de um investimento
    void previsaoInvestimento(){
        // Declara��o das vari�veis
        float investimentoInicial, taxa, investimentoMensal, resultado;
        int periodo, i;

        // Leitura dos dados
        printf("Escreva o valor do investimento inicial: ");
        scanf("%f", &investimentoInicial);

        printf("\n Informe a taxa de rendimento mensal em porcentagem");
        printf("\n Ex: 0,05 para 5%% (use a v�rgula como separador)");
        printf("\n Taxa: ");
        scanf("%f", &taxa);

        printf("\n Informe o valor que investir� mensalmente: ");
        scanf("%f", &investimentoMensal);

        printf("\nInforme o per�odo em meses: ");
        scanf("%d", &periodo);

        // Inicializando as vari�veis
        resultado = investimentoInicial;
        i = 1;

        // loop para calcular a previs�o
        while (i <= periodo) {
            resultado += investimentoMensal;
            resultado += resultado * (taxa / 100);
            i++;
        }
        printf("Ap�s o per�odo de %d meses, o valor do investimento ser� de R$ %.2f\n", periodo, resultado);
    }
    
