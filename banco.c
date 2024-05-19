#include "banco.h"
#include <stdio.h>
#include <string.h>

ERROS criar(Cliente clientes[], int *pos) {
  if (*pos >= TOTAL) {      // Verifica se já atingiu o limite de clientes
    return LIMITE_CLIENTES; // Retorna o erro caso tenha atingido o limite
  }

  printf("Digite o seu nome: ");
  fgets(clientes[*pos].nome, NOME, stdin); // Lê o nome do cliente

  do {
    printf("Entre com o seu CPF (11 dígitos): ");
    fgets(clientes[*pos].cpf, sizeof(clientes[*pos].cpf),
          stdin); // Lê o CPF do cliente
    clientes[*pos].cpf[strcspn(clientes[*pos].cpf, "\n")] =
        '\0'; // Remove o caractere de nova linha

    if (strlen(clientes[*pos].cpf) != 11) { // Verifica se o CPF tem 11 dígitos
      printf("O CPF deve conter 11 dígitos.\n");
    }
  } while (strlen(clientes[*pos].cpf) !=
           11); // Continua pedindo o CPF até que tenha 11 dígitos

  printf("A sua conta será COMUM ou PLUS? ");
  fgets(clientes[*pos].conta, CONTA, stdin); // Lê o tipo de conta do cliente

  printf("Qual será o valor inicial da sua conta? ");
  scanf("%f", &clientes[*pos].saldo); // Lê o saldo inicial do cliente

  clearBuffer(); // Limpa o buffer novamente

  do {
    printf("Crie uma senha com 8 dígitos: ");
    fgets(clientes[*pos].senha, sizeof(clientes[*pos].senha),
          stdin); // Lê a senha do cliente

    // Remove a quebra de linha se existir
    clientes[*pos].senha[strcspn(clientes[*pos].senha, "\n")] = '\0';

    if (strlen(clientes[*pos].senha) !=
        8) { // Verifica se a senha tem 8 dígitos
      printf("A senha deve ter 8 dígitos.\n");
    }
  } while (strlen(clientes[*pos].senha) !=
           8); // Continua pedindo a senha até que tenha 8 dígitos

  *pos = *pos + 1; // Incrementa a posição do array de clientes
  printf(
      "\nConta criada com sucesso!\nSeja bem vindo ao CBank <3\n"); // Mensagem
                                                                    // de
                                                                    // sucesso
  return OK; // Retorna OK para indicar que a operação foi concluída com sucesso
}

ERROS deletar(Cliente clientes[], int *pos) {
  char cpf[CPF]; // Variável para armazenar o CPF a ser excluído
  int i, j;
  printf("Digite o CPF do cliente que deseja excluir: ");
  fgets(cpf, sizeof(cpf), stdin); // Lê o CPF do cliente a ser excluído
  cpf[strcspn(cpf, "\n")] = '\0'; // Remove o caractere de nova linha

  // Procura o cliente pelo CPF
  for (i = 0; i < *pos; i++) {
    if (strcmp(clientes[i].cpf, cpf) ==
        0) { // Se encontrar o cliente com o CPF fornecido
      // Move todos os clientes após o cliente a ser excluído uma posição para
      // frente
      for (j = i; j < *pos - 1; j++) {
        strcpy(clientes[j].nome, clientes[j + 1].nome);
        strcpy(clientes[j].cpf, clientes[j + 1].cpf);
        strcpy(clientes[j].conta, clientes[j + 1].conta);
        clientes[j].saldo = clientes[j + 1].saldo;
        strcpy(clientes[j].senha, clientes[j + 1].senha);
      }
      // Decrementa o número total de clientes
      *pos = *pos - 1;
      printf("Cliente excluído com sucesso.\n");

      // Se não houver mais clientes, redefine pos como 0
      if (*pos == 0) {
        *pos = 0;
      }

      return OK; // Retorna OK para indicar que o cliente foi excluído com
                 // sucesso
    }
  }
  // Se não encontrar o cliente com o CPF fornecido, exibe mensagem de erro
  printf("Cliente com CPF %s não encontrado.\n", cpf);
  return CLIENTE_NAO_ENCONTRADO; // Retorna erro indicando que o cliente não foi
                                 // encontrado
}

ERROS listar(Cliente clientes[], int *pos) {
  if (*pos == 0) {
    return SEM_CLIENTES;
  }

  for (int i = 0; i < *pos; i++) { // inicial o loop
    printf("\nNome: %s", clientes[i].nome);
    printf("CPF: %s\n", clientes[i].cpf);
    printf("Conta: %s", clientes[i].conta);
    printf("Saldo: %.2f\n", clientes[i].saldo);
    printf("Senha: %s\n", clientes[i].senha);
  }

  printf("\nClientes listados com sucesso! <3\n");
  return OK;
}

ERROS salvarbinario(Cliente clientes[], int *pos) {
  FILE *arquivo = fopen("contas.bin", "wb");

  if (arquivo == NULL) {
    return ABRIR; // Retornar erro
  }

  // Escrever os dados dos clientes no arquivo
  if (fwrite(clientes, sizeof(Cliente), pos, arquivo) != pos) {
    fclose(arquivo); // Fechar o arquivo antes de retornar o erro
    return ESCRITA;  // Retornar erro de escrita
  }

  fclose(arquivo);
  printf("Dados salvos com sucesso.\n");
  return OK; // Retornar OK
}

ERROS debito(Cliente clientes[], int *pos) {
    char cpf[CPF]; // Variável para armazenar o CPF
    char senha[SENHA]; // Variável para armazenar a senha
    int valor; // Variável para armazenar o valor a ser debitado
    int i;

    printf("Digite o CPF do cliente: ");
    fgets(cpf, sizeof(cpf), stdin); // Lê o CPF do cliente
    cpf[strcspn(cpf, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Digite a senha da conta: ");
    fgets(senha, sizeof(senha), stdin); // Lê a senha da conta
    senha[strcspn(senha, "\n")] = '\0'; // Remove o caractere de nova linha

    // Procura o cliente pelo CPF
    for (i = 0; i < *pos; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) { // Se encontrar o cliente com o CPF fornecido
            if (strcmp(clientes[i].senha, senha) == 0) { // Verifica se a senha está correta
                printf("Digite o valor a ser debitado: ");
                scanf("%d", &valor); // Lê o valor a ser debitado

                // Verifica se há saldo suficiente na conta
                if (clientes[i].saldo >= valor) {
                    clientes[i].saldo -= valor; // Debita o valor da conta
                    printf("Valor debitado com sucesso.\n");
                    return OK; // Retorna OK indicando que o débito foi realizado com sucesso
                } else {
                    printf("Saldo insuficiente.\n");
                    return SALDO_INSUFICIENTE; // Retorna erro indicando saldo insuficiente
                }
            } else {
                printf("Senha incorreta.\n");
                return SENHA_INCORRETA; // Retorna erro indicando senha incorreta
            }
        }
    }

    printf("Cliente com CPF %s não encontrado.\n", cpf);
    return CLIENTE_NAO_ENCONTRADO; // Retorna erro indicando que o cliente não foi encontrado
}

ERROS deposito(Cliente clientes[], int *pos) {
  char cpf[CPF]; // Variável para armazenar o CPF
  int valor; // Variável para armazenar o valor a ser debitado
  int i;

  printf("Digite o CPF do cliente: ");
  fgets(cpf, sizeof(cpf), stdin); // Lê o CPF do cliente
  cpf[strcspn(cpf, "\n")] = '\0'; // Remove o caractere de nova linha

  // Procura o cliente pelo CPF
  for (i = 0; i < *pos; i++) {
    if (strcmp(clientes[i].cpf, cpf) == 0) { // Se encontrar o cliente com o CPF fornecido
      printf("Digite o valor a ser depositado: ");
      scanf("%d", &valor); // Lê o valor a ser debitado
      clientes[i].saldo += valor; // Debita o valor da conta
      printf("Valor depositado com sucesso.\n");
      return OK; // Retorna OK indicando que o débito foi realizado com sucesso
    } else {
      printf("Cliente com CPF %s não encontrado.\n", cpf);
      return CLIENTE_NAO_ENCONTRADO; // Retorna erro indicando que o cliente não foi encontrado
      }
  }
  return OK;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ; // Limpa o buffer de entrada
}