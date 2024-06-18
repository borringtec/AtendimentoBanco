#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define MAX_CLIENTES 100

typedef struct {
    char nome[100], cpf[15];
    int tipoAtendimento;
} Cliente;

void pause() {
    printf("Pressione qualquer tecla para voltar...");
    while ((getchar()) != '\n');
    getchar();
    system(CLEAR);
}

void opcaoInvalida() {
    printf("Opção inválida! Tente novamente.\n");
}

void formatarCPF(char *cpf) {
    int j = 0;
    for (int i = 0; cpf[i] != '\0'; i++)
        if (isdigit((unsigned char)cpf[i])) cpf[j++] = cpf[i];
    printf("CPF: %.3s.%.3s.%.3s-%.2s\n", cpf, cpf + 3, cpf + 6, cpf + 9);
}

void listarMenuPrincipal() {
    printf(
        "Bem-vindo ao sistema de atendimento\n"
        "1 - Solicitar Atendimento\n"
        "2 - Listar Atendimentos Registrados\n"
        "3 - Listar Atendimento por Setor\n"
        "4 - Sair\n"
        "Opção: "
    );
}

void listarTipoAtendimento() {
    printf(
        "Escolha o tipo de atendimento:\n"
        "1 - Abertura de Conta\n"
        "2 - Caixa\n"
        "3 - Gerente Pessoa Física\n"
        "4 - Gerente Pessoa Jurídica\n"
        "5 - Voltar ao Menu Principal\n"
        "Opção: "
    );
}

void registrarAtendimento(Cliente *cliente, int *contador) {
    int escolha;
    do {
        listarTipoAtendimento();
        if (scanf("%d", &escolha) == 0) escolha = getchar();
        system(CLEAR);
        switch (escolha) {
        case 1 ... 4:
            printf("Digite o nome do cliente: ");
            while ((getchar()) != '\n');
            fgets(cliente[*contador].nome, sizeof(cliente[*contador].nome), stdin);
            printf("Digite o CPF do cliente: ");
            scanf("%s", cliente[*contador].cpf);
            system(CLEAR);
            cliente[*contador].tipoAtendimento = escolha;
            (*contador)++;
            printf("Atendimento registrado com sucesso!\n");
            break;
        case 5:
            break;
        default:
            opcaoInvalida();
            break;
        }
    } while (escolha != 5);
}

void listarAtendimento(Cliente *cliente) {
    printf("Nome: %s", cliente->nome);
    formatarCPF(cliente->cpf);
    printf("Tipo Atendimento - %d - ", cliente->tipoAtendimento);
    switch (cliente->tipoAtendimento) {
    case 1: printf("Abertura de Conta\n"); break;
    case 2: printf("Caixa\n"); break;
    case 3: printf("Gerente Pessoa Física\n"); break;
    case 4: printf("Gerente Pessoa Jurídica\n"); break;
    }
    printf("==============================================\n");
}

void listarPorTipoAtendimento(Cliente *clientes, int contador, int escolha) {
    for (int i = 0; i < contador; i++)
        if (clientes[i].tipoAtendimento == escolha) listarAtendimento(&clientes[i]);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    Cliente clientes[MAX_CLIENTES];
    int contador = 0, escolha;
    do {
        listarMenuPrincipal();
        if (scanf("%d", &escolha) == 0) escolha = getchar();
        system(CLEAR);
        switch (escolha) {
        case 1:
            if (contador < MAX_CLIENTES) registrarAtendimento(clientes, &contador);
            else printf("Limite de clientes atingido.\n");
            break;
        case 2:
            system(CLEAR);
            for (int i = 0; i < contador; i++)
                listarAtendimento(&clientes[i]);
            pause();
            break;
        case 3:
            do {
                listarTipoAtendimento();
                if (scanf("%d", &escolha) == 0) escolha = getchar();
                system(CLEAR);
                switch (escolha) {
                case 1 ... 4:
                    listarPorTipoAtendimento(clientes, contador, escolha);
                    pause();
                    break;
                case 5:
                    break;
                default:
                    opcaoInvalida();
                    break;
                }
            } while (escolha != 5);
            break;
        case 4:
            break;
        default:
            opcaoInvalida();
            break;
        }
    } while (escolha != 4);
    return 0;
}