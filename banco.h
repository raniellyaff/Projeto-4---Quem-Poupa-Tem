#include <stdio.h>
#include <string.h>

#define TOTAL 1000
#define NOME 50
#define CONTA 10
#define SENHA 10
#define CPF 13
#define TIPO 3
#define MAX_OPERACOES 100

// Estrutura para representar uma operação no extrato
typedef struct Historico {
    char tipo_operacao[20];
    float valor;
    float tarifa;
} Operacao;

typedef enum {
    COMUM,
    PLUS
} TipoConta;

typedef struct Cliente {
    char nome[NOME];
    char cpf[CPF];
    TipoConta tipo_conta;
    char senha[SENHA];
    float saldo;
    char conta[CONTA];
    Operacao historico_operacoes[MAX_OPERACOES];
    int num_operacoes;
} Cliente;

typedef enum {
    OK,
    SENHA_CURTA,
    LIMITE_CLIENTES,
    CPF_INVALIDO,
    CLIENTE_NAO_ENCONTRADO,
    SEM_CLIENTES,
    LISTA_VAZIA,
    ABRIR,
    ESCRITA,
    SALDO_INSUFICIENTE,
    SENHA_INCORRETA,
    ERRO_ARQUIVO,
    CREDENCIAIS_INVALIDAS,
} ERROS;

typedef ERROS (*funcao)(Cliente[], int *);

ERROS criar(Cliente clientes[], int *pos);
ERROS deletar(Cliente clientes[], int *pos);
ERROS listar(Cliente clientes[], int *pos);
ERROS salvarbinario(Cliente clientes[], int *pos);
ERROS debito(Cliente clientes[], int *pos);
ERROS deposito(Cliente clientes[], int *pos);
ERROS pix(Cliente clientes[], int *pos);
ERROS extrato(Cliente clientes[], int *pos);

void clearBuffer();
