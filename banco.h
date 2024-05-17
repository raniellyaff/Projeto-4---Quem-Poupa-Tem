#define TOTAL 1000
#define NOME 50
#define CONTA 10
#define SENHA 10
#define CPF 13

typedef struct Cliente {
  char nome[NOME];
  char cpf[CPF];
  char senha[SENHA];
  int saldo;
  char conta[CONTA];
  int limiteNegativo;
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
  CONTA_INVALIDA,
} ERROS;

typedef ERROS (*funcao)(Cliente[], int *);

ERROS criar(Cliente clientes[], int *pos);
ERROS deletar(Cliente clientes[], int *pos);
ERROS listar(Cliente clientes[], int *pos);
ERROS salvarbinario(Cliente clientes[], int *pos);

void clearBuffer();
