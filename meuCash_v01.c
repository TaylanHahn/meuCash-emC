/******************************************************************************
APP MEU CASH 

É um programa de controle financeiro simples que permite registrar ganhos e gastos fixos, ganhos e gastos eventuais e exibir o saldo atual.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

void registrarGanhosFixos();
void registrarSaidasFixas();
void registrarGanhosEventuais();
void registrarSaidasEventuais();
void atualizarSaldo();
void exibirExtrato();
void registrarTransacao(float valor, const char* tipo, const char* natureza);
void calculadoraSimples();
void previsaoInvestimento();
void salvarDados();
void carregarDados();
void formatarDados();

float ganhosFixos = 0.0f, saidasFixas = 0.0f, ganhosEventuais = 0.0f, saidasEventuais = 0.0f, saldo = 0.0f;

#define MAX_TRANSACOES 50
typedef struct {
    float valor;
    char tipo[16];     // "Fixa" ou "Eventual"
    char natureza[16]; // "Entrada" ou "Saida"
} Transacao;

Transacao transacoes[MAX_TRANSACOES];
int totalTransacoes = 0;

int main() {
    /* Configura o locale para Português (padrão pode variar por sistema) */
    setlocale(LC_ALL, "Portuguese_Brazil");

    carregarDados(); // Carrega os dados do arquivo ao iniciar

    printf("\tBem-vindo ao MeuCASH\n");
    printf("\tO app ideal para o seu controle financeiro\n");

    int opcao;
    do {
        printf("---------------------------------------------------------------------\n");
        printf("\n\t~~~ Escolha uma função ~~~\n");
        printf("\t(Digite apenas o número da opção desejada)\n\n");
        printf("\t1 - Registrar ganhos fixos\n");
        printf("\t2 - Registrar gastos fixos\n");
        printf("\t3 - Registrar ganhos eventuais\n");
        printf("\t4 - Registrar gastos eventuais\n");
        printf("\t5 - Exibir saldo atual\n");
        printf("\t6 - Exibir extrato\n");
        printf("\n\t~~~ Funções extras ~~~\n\n");
        printf("\t7 - Calculadora simples\n");
        printf("\t8 - Calcular previsão de investimentos\n");
        printf("\n\t~~~ Encerrar operações ~~~\n\n");
        printf("\t9 - Formatar todos os dados\n");
        printf("\t10 - Salvar e Sair\n");
        printf("\t11 - Sair\n\n");
        printf("---------------------------------------------------------------------\n");

        if (scanf("%d", &opcao) != 1) {
            /* Entrada inválida: consome o que restou e continua */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("\nEntrada inválida. Digite um número.\n");
            opcao = 0;
        }

        /* Limpa a tela de forma portátil */
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

        switch (opcao) {
            case 1: registrarGanhosFixos(); break;
            case 2: registrarSaidasFixas(); break;
            case 3: registrarGanhosEventuais(); break;
            case 4: registrarSaidasEventuais(); break;
            case 5: printf("\nSeu saldo atual é de R$ %.2f\n", saldo); break;
            case 6: exibirExtrato(); break;
            case 7: calculadoraSimples(); break;
            case 8: previsaoInvestimento(); break;
            case 9: formatarDados(); break;
            case 10: salvarDados(); printf("\nSalvando e saindo do app...\n"); break;
            case 11: printf("\nSaindo do aplicativo...\n"); break;
            default: if (opcao != 0) printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 10 && opcao != 11);

    return 0;
}

/* ======================================== Funções de Registro ======================================== */

/* Registro de GANHOS FIXOS */
void registrarGanhosFixos() {
    double valor;
    printf("Informe o valor dos ganhos fixos: ");
    if (scanf("%lf", &valor) == 1) {
        ganhosFixos += (float)valor;
        atualizarSaldo();
        registrarTransacao((float)valor, "Fixa", "Entrada");
        salvarDados();
    } else {
        printf("Entrada inválida.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
    }
}

/* Registro de SAÍDAS FIXAS */
void registrarSaidasFixas() {
    double valor;
    printf("Informe o valor das saídas fixas: ");
    if (scanf("%lf", &valor) == 1) {
        saidasFixas += (float)valor;
        atualizarSaldo();
        registrarTransacao((float)valor, "Fixa", "Saida");
        salvarDados();
    } else {
        printf("Entrada inválida.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
    }
}

/* Registrar GANHOS EVENTUAIS */
void registrarGanhosEventuais() {
    double valor;
    printf("Informe o valor de ganhos eventuais: ");
    if (scanf("%lf", &valor) == 1) {
        ganhosEventuais += (float)valor;
        atualizarSaldo();
        registrarTransacao((float)valor, "Eventual", "Entrada");
        salvarDados();
    } else {
        printf("Entrada inválida.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
    }
}

/* Registrar SAÍDAS EVENTUAIS */
void registrarSaidasEventuais() {
    double valor;
    printf("Informe o valor de saídas eventuais: ");
    if (scanf("%lf", &valor) == 1) {
        saidasEventuais += (float)valor;
        atualizarSaldo();
        registrarTransacao((float)valor, "Eventual", "Saida");
        salvarDados();
    } else {
        printf("Entrada inválida.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
    }
}

/* Atualizar saldo */
void atualizarSaldo() {
    saldo = ganhosFixos - saidasFixas + ganhosEventuais - saidasEventuais;
}

/* Registrar transação (mantém um buffer cíclico de MAX_TRANSACOES) */
void registrarTransacao(float valor, const char* tipo, const char* natureza) {
    if (totalTransacoes < MAX_TRANSACOES) {
        transacoes[totalTransacoes].valor = valor;
        snprintf(transacoes[totalTransacoes].tipo, sizeof(transacoes[totalTransacoes].tipo), "%s", tipo);
        snprintf(transacoes[totalTransacoes].natureza, sizeof(transacoes[totalTransacoes].natureza), "%s", natureza);
        totalTransacoes++;
    } else {
        /* remove o mais antigo e desloca */
        for (int i = 1; i < MAX_TRANSACOES; i++) {
            transacoes[i - 1] = transacoes[i];
        }
        transacoes[MAX_TRANSACOES - 1].valor = valor;
        snprintf(transacoes[MAX_TRANSACOES - 1].tipo, sizeof(transacoes[MAX_TRANSACOES - 1].tipo), "%s", tipo);
        snprintf(transacoes[MAX_TRANSACOES - 1].natureza, sizeof(transacoes[MAX_TRANSACOES - 1].natureza), "%s", natureza);
    }
}

/* =================================== Funções de Memória ============================================== */

/* Exibir extrato — últimas 5 entradas e últimas 5 saídas */
void exibirExtrato() {
    int entradas = 0, saidas = 0;

    printf("\nÚltimas 5 Entradas:\n");
    for (int i = totalTransacoes - 1; i >= 0 && entradas < 5; i--) {
        if (strcmp(transacoes[i].natureza, "Entrada") == 0) {
            printf("Valor: R$ %.2f | Tipo: %s\n", transacoes[i].valor, transacoes[i].tipo);
            entradas++;
        }
    }

    printf("\nÚltimas 5 Saídas:\n");
    for (int i = totalTransacoes - 1; i >= 0 && saidas < 5; i--) {
        if (strcmp(transacoes[i].natureza, "Saida") == 0) {
            printf("Valor: R$ %.2f | Tipo: %s\n", transacoes[i].valor, transacoes[i].tipo);
            saidas++;
        }
    }
}

/* Salvar dados em arquivo texto */
void salvarDados() {
    FILE *arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar os dados!\n");
        return;
    }

    /* Grava os valores globais */
    fprintf(arquivo, "%.2f %.2f %.2f %.2f %.2f\n", ganhosFixos, saidasFixas, ganhosEventuais, saidasEventuais, saldo);

    /* Salva o número de transações */
    fprintf(arquivo, "%d\n", totalTransacoes);

    /* Salva cada transação (tipo e natureza sem espaços) */
    for (int i = 0; i < totalTransacoes; i++) {
        fprintf(arquivo, "%.2f %s %s\n", transacoes[i].valor, transacoes[i].tipo, transacoes[i].natureza);
    }

    fclose(arquivo);
    printf("\nDados salvos com sucesso!\n\n");
}

/* Carregar dados do arquivo (se existir) */
void carregarDados() {
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        /* arquivo não existe: usa valores zerados */
        return;
    }

    /* Lê os valores gravados anteriormente.
       Usamos retorno de fscanf para evitar comportamentos indefinidos. */
    if (fscanf(arquivo, "%f %f %f %f %f", &ganhosFixos, &saidasFixas, &ganhosEventuais, &saidasEventuais, &saldo) != 5) {
        /* Arquivo corrompido ou formato inesperado */
        fclose(arquivo);
        return;
    }

    if (fscanf(arquivo, "%d", &totalTransacoes) != 1) {
        totalTransacoes = 0;
    }

    /* Protege contra arquivos com contador maior que MAX_TRANSACOES */
    if (totalTransacoes < 0) totalTransacoes = 0;
    if (totalTransacoes > MAX_TRANSACOES) totalTransacoes = MAX_TRANSACOES;

    for (int i = 0; i < totalTransacoes; i++) {
        /* lê valor, tipo e natureza */
        if (fscanf(arquivo, "%f %15s %15s", &transacoes[i].valor, transacoes[i].tipo, transacoes[i].natureza) != 3) {
            /* falha na leitura: zera restante */
            transacoes[i].valor = 0.0f;
            strcpy(transacoes[i].tipo, "");
            strcpy(transacoes[i].natureza, "");
        }
    }

    fclose(arquivo);
    atualizarSaldo();
    printf("\nDados carregados com sucesso!\n\n");
}

/* Formatar (zerar) todos os dados */
void formatarDados() {
    ganhosFixos = 0.0f;
    saidasFixas = 0.0f;
    ganhosEventuais = 0.0f;
    saidasEventuais = 0.0f;
    saldo = 0.0f;
    totalTransacoes = 0;

    for (int i = 0; i < MAX_TRANSACOES; i++) {
        transacoes[i].valor = 0.0f;
        strcpy(transacoes[i].tipo, "");
        strcpy(transacoes[i].natureza, "");
    }

    salvarDados();
    printf("\nTodos os dados foram formatados com sucesso!\n\n");
}

/* ============================================ Funções Extras ========================================= */

/* Calculadora simples */
void calculadoraSimples() {
    float num1, num2, resultado;
    char operador;

    printf("Informe o primeiro número: ");
    if (scanf("%f", &num1) != 1) {
        printf("Entrada inválida.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }

    printf("Insira apenas o símbolo do operador \n(+ para adição, - para subtração, * para multiplicação, / para divisão): ");
    scanf(" %c", &operador);

    printf("Informe o segundo número: ");
    if (scanf("%f", &num2) != 1) {
        printf("Entrada inválida.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }

    if (operador == '+') {
        resultado = num1 + num2;
        printf("\nResultado: %.2f\n", resultado);
    } else if (operador == '-') {
        resultado = num1 - num2;
        printf("\nResultado: %.2f\n", resultado);
    } else if (operador == '*') {
        resultado = num1 * num2;
        printf("\nResultado: %.2f\n", resultado);
    } else if (operador == '/') {
        if (num2 != 0.0f) {
            resultado = num1 / num2;
            printf("\nResultado: %.2f\n", resultado);
        } else {
            printf("\nErro: Divisão por zero não permitida.\n");
        }
    } else {
        printf("\nOperador inválido.\n");
    }
}

/* Previsão de investimento (juros compostos com aporte mensal) */
void previsaoInvestimento() {
    float investimentoInicial, taxa, investimentoMensal, resultado;
    int periodo, i;

    printf("Escreva o valor do investimento inicial: ");
    if (scanf("%f", &investimentoInicial) != 1) {
        printf("Entrada inválida.\n"); int c; while ((c = getchar()) != '\n' && c != EOF) {} return;
    }

    printf("\n Informe a taxa de rendimento mensal em porcentagem\n");
    printf(" Ex: 5 para 5%% (use ponto ou vírgula conforme seu sistema)\n");
    printf(" Taxa: ");
    if (scanf("%f", &taxa) != 1) {
        printf("Entrada inválida.\n"); int c; while ((c = getchar()) != '\n' && c != EOF) {} return;
    }

    printf("\n Informe o valor que investirá mensalmente: ");
    if (scanf("%f", &investimentoMensal) != 1) {
        printf("Entrada inválida.\n"); int c; while ((c = getchar()) != '\n' && c != EOF) {} return;
    }

    printf("\nInforme o período em meses: ");
    if (scanf("%d", &periodo) != 1) {
        printf("Entrada inválida.\n"); int c; while ((c = getchar()) != '\n' && c != EOF) {} return;
    }

    resultado = investimentoInicial;
    for (i = 1; i <= periodo; i++) {
        resultado += investimentoMensal;
        resultado += resultado * (taxa / 100.0f);
    }

    printf("Após o período de %d meses, o valor do investimento será de R$ %.2f\n", periodo, resultado);
}
