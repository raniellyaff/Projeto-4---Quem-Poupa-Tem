#define TOTAL 1000
#define NOME 50
#define CONTA 5
#define SENHA 10
#define CPF 13

typedef struct Cliente {
    char nome[NOME];
    char cpf[CPF];
    char senha[SENHA];
    int saldo;
    char conta[CONTA];
} Cliente;

typedef enum {OK, SENHA_CURTA, LIMITE_CLIENTES, CPF_INVALIDO} ERROS;

typedef ERROS (*funcao)(Cliente[], int*);

ERROS criar (Cliente clientes[], int *pos);

void clearBuffer();

