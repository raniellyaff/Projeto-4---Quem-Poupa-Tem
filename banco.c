#include "banco.h"
#include <stdio.h>
#include <string.h>

ERROS criar(Cliente clientes[], int *pos) {
  if (*pos >= TOTAL) { // Verifica se já atingiu o limite de clientes
    return LIMITE_CLIENTES; // Retorna o erro caso tenha atingido o limite
  }

  printf("Digite o seu nome: ");
  fgets(clientes[*pos].nome, NOME, stdin); // Lê o nome do cliente

  do {
    printf("Entre com o seu CPF (11 dígitos): ");
    fgets(clientes[*pos].cpf, sizeof(clientes[*pos].cpf), stdin); // Lê o CPF do cliente
    clientes[*pos].cpf[strcspn(clientes[*pos].cpf, "\n")] = '\0'; // Remove o caractere de nova linha

    if (strlen(clientes[*pos].cpf) != 11) { // Verifica se o CPF tem 11 dígitos
      printf("O CPF deve conter 11 dígitos.\n");
      clearBuffer(); // Limpa o buffer para remover caracteres extras
    }
  } while (strlen(clientes[*pos].cpf) != 11); // Continua pedindo o CPF até que tenha 11 dígitos

  printf("A sua conta será COMUM ou PLUS? ");
  fgets(clientes[*pos].conta, CONTA, stdin); // Lê o tipo de conta do cliente

  clearBuffer(); // Limpa o buffer para evitar problemas na leitura futura

  printf("Qual será o valor inicial da sua conta? ");
  scanf("%d", &clientes[*pos].saldo); // Lê o saldo inicial do cliente

  clearBuffer(); // Limpa o buffer novamente

  do {
    printf("Crie uma senha de até 8 dígitos: ");
    fgets(clientes[*pos].senha, sizeof(clientes[*pos].senha), stdin); // Lê a senha do cliente

    // Remove a quebra de linha se existir
    clientes[*pos].senha[strcspn(clientes[*pos].senha, "\n")] = '\0';

    if (strlen(clientes[*pos].senha) != 8) { // Verifica se a senha tem 8 dígitos
      printf("A senha deve ter 8 dígitos.\n");
      clearBuffer(); // Limpa o buffer para remover caracteres extras
    }
  } while (strlen(clientes[*pos].senha) != 8); // Continua pedindo a senha até que tenha 8 dígitos

  *pos = *pos + 1; // Incrementa a posição do array de clientes
  printf("\nConta Criada com sucesso!\nSeja bem vindo ao CBank <3\n"); // Mensagem de sucesso

  return OK; // Retorna OK para indicar que a operação foi concluída com sucesso
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
}