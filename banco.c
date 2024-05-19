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
    fgets(clientes[*pos].cpf, sizeof(clientes[*pos].cpf), stdin); // Lê o CPF do cliente
    clientes[*pos].cpf[strcspn(clientes[*pos].cpf, "\n")] = '\0'; // Remove o caractere de nova linha

    if (strlen(clientes[*pos].cpf) != 11) { // Verifica se o CPF tem 11 dígitos
      printf("O CPF deve conter 11 dígitos.\n");
    }
  } while (strlen(clientes[*pos].cpf) != 11); // Continua pedindo o CPF até que tenha 11 dígitos

  char tipo[TIPO]; // Definindo a variável tipo para armazenar a entrada do usuário
  
  do {
      printf("A sua conta será COMUM (C) ou PLUS (P)? ");
      fgets(tipo, TIPO, stdin); // Lê o tipo de conta do cliente
      if (tipo[0] == 'C' || tipo[0] == 'P'){
        clientes[*pos].tipo_conta = (tipo[0] == 'C')  ? COMUM : PLUS;
      }else{
        printf("Tipo de conta inválido. Escolha 'C' para Comum ou 'P' para Plus.\n");
      }
  } while (clientes[*pos].tipo_conta != COMUM && clientes[*pos].tipo_conta != PLUS);

  printf("Qual será o valor inicial da sua conta? ");
  scanf("%f", &clientes[*pos].saldo); // Lê o saldo inicial do cliente

  clearBuffer(); // Limpa o buffer novamente
  
  do {
    printf("Crie uma senha com 8 dígitos: ");
    fgets(clientes[*pos].senha, sizeof(clientes[*pos].senha), stdin); // Lê a senha do cliente
    // Remove a quebra de linha se existir
    clientes[*pos].senha[strcspn(clientes[*pos].senha, "\n")] = '\0';
    if (strlen(clientes[*pos].senha) != 8) { // Verifica se a senha tem 8 dígitos
      printf("A senha deve ter 8 dígitos.\n");
    }
  } while (strlen(clientes[*pos].senha) != 8); // Continua pedindo a senha até que tenha 8 dígitos

  *pos = *pos + 1; // Incrementa a posição do array de clientes
  printf("\nConta criada com sucesso!\nSeja bem vindo ao CBank <3\n"); // Mensagem de sucesso
  return OK; // Retorna OK para indicar que a operação foi concluída com sucesso
  clearBuffer();
}

ERROS deletar(Cliente clientes[], int *pos) {
  char cpf[CPF]; // Variável para armazenar o CPF a ser excluído
  int i, j;
  printf("Digite o CPF do cliente que deseja excluir: ");
  fgets(cpf, sizeof(cpf), stdin); // Lê o CPF do cliente a ser excluído
  cpf[strcspn(cpf, "\n")] = '\0'; // Remove o caractere de nova linha

  // Procura o cliente pelo CPF
  for (i = 0; i < *pos; i++) {
    if (strcmp(clientes[i].cpf, cpf) == 0) { // Se encontrar o cliente com o CPF fornecido
      // Move todos os clientes após o cliente a ser excluído uma posição para frente
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
      return OK; // Retorna OK para indicar que o cliente foi excluído com sucesso
    }
  }
  // Se não encontrar o cliente com o CPF fornecido, exibe mensagem de erro
  printf("Cliente com CPF %s não encontrado.\n", cpf);
  return CLIENTE_NAO_ENCONTRADO; // Retorna erro indicando que o cliente não foi encontrado
  clearBuffer();
}

ERROS listar(Cliente clientes[], int *pos) {
  if (*pos == 0) {
    return SEM_CLIENTES;
  }

  for (int i = 0; i < *pos; i++) { // inicial o loop
    printf("\nNome: %s", clientes[i].nome);
    printf("CPF: %s\n", clientes[i].cpf);
    printf("Conta: %s\n", clientes[i].tipo_conta == COMUM ? "COMUM" : "PLUS");
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
  clearBuffer();
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
        float taxa = (clientes[i].tipo_conta == COMUM) ? 0.05f : 0.03f; // Taxa de acordo com o tipo de conta
        float valor_debitado = valor * (1 + taxa);
        float saldo_negativo_maximo = (clientes[i].tipo_conta == COMUM) ? -1000.0f : -5000.0f; // Limite de saldo negativo
        if (clientes[i].saldo - valor_debitado >= saldo_negativo_maximo) {
            clientes[i].saldo -= valor_debitado; // Debita o valor da conta
            printf("Valor debitado com sucesso.\n");
            return OK; // Retorna OK indicando que o débito foi realizado com sucesso
        } else {
            printf("Saldo insuficiente ou limite de saldo negativo excedido.\n");
            return SALDO_INSUFICIENTE; // Retorna erro indicando saldo insuficiente ou limite de saldo negativo excedido
            }
      }else {
        printf("Senha incorreta.\n");
        return SENHA_INCORRETA; // Retorna erro indicando senha incorreta
      }
    }
  }
  printf("Cliente com CPF %s não encontrado.\n", cpf);
  clearBuffer();
  return CLIENTE_NAO_ENCONTRADO; // Retorna erro indicando que o cliente não foi encontrado
}

ERROS deposito(Cliente clientes[], int *pos) {
  char cpf[CPF]; // Variável para armazenar o CPF
  int valor; // Variável para armazenar o valor a ser depositado
  int i;

  printf("Digite o CPF do cliente: ");
  fgets(cpf, sizeof(cpf), stdin); // Lê o CPF do cliente
  cpf[strcspn(cpf, "\n")] = '\0'; // Remove o caractere de nova linha

  // Procura o cliente pelo CPF
  for (i = 0; i < *pos; i++) {
    if (strcmp(clientes[i].cpf, cpf) == 0) { // Se encontrar o cliente com o CPF fornecido
      printf("Digite o valor a ser depositado: ");
      scanf("%d", &valor); // Lê o valor a ser depositado
      clientes[i].saldo += valor; // Credita o valor na conta
      clearBuffer(); // Limpa o buffer após scanf
      printf("Valor depositado com sucesso.\n");
      return OK; // Retorna OK indicando que o depósito foi realizado com sucesso
    }
  }

  // Se não encontrar o cliente com o CPF fornecido, exibe mensagem de erro
  printf("Cliente com CPF %s não encontrado.\n", cpf);
  clearBuffer(); // Limpa o buffer após fgets
  return CLIENTE_NAO_ENCONTRADO; // Retorna erro indicando que o cliente não foi encontrado
}

ERROS pix(Cliente clientes[], int *pos) {
    char cpfOrigem[CPF]; // Variável para armazenar o CPF
    char senha[SENHA]; // Variável para armazenar a senha
    char cpfDestino[CPF];
    float valor; // Variável para armazenar o valor a ser debitado
    int i;
    int j;
    int clienteDestinoEncontrado = 0;

    printf("Digite o CPF da conta de origem: ");
    fgets(cpfOrigem, sizeof(cpfOrigem), stdin);
    cpfOrigem[strcspn(cpfOrigem, "\n")] = '\0';

    printf("Digite a senha da conta de origem: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0';

    printf("Digite o CPF da conta de destino: ");
    fgets(cpfDestino, sizeof(cpfDestino), stdin);
    cpfDestino[strcspn(cpfDestino, "\n")] = '\0';

    printf("Digite o valor a ser transferido: ");
    scanf("%f", &valor);
    clearBuffer(); // Limpa o buffer após scanf

    for (i = 0; i < *pos; i++) {
        if (strcmp(clientes[i].cpf, cpfOrigem) == 0) {
            // Verifica se a senha está correta
            if (strcmp(clientes[i].senha, senha) == 0) {
                // Verifica se o saldo é suficiente para transferência
                if (clientes[i].saldo >= valor) {
                    // Procura o cliente de destino
                    for (j = 0; j < *pos; j++) {
                        if (strcmp(clientes[j].cpf, cpfDestino) == 0) {
                            // Realiza a transferência
                            clientes[i].saldo -= valor;
                            clientes[j].saldo += valor;
                            printf("Transferência realizada com sucesso.\n");
                            return OK;
                        }
                    }
                    // Se chegou aqui, a conta de destino não foi encontrada
                    printf("Conta de destino não encontrada.\n");
                    return CLIENTE_NAO_ENCONTRADO;
                } else {
                    printf("Saldo insuficiente.\n");
                    return SALDO_INSUFICIENTE;
                }
            } else {
                printf("Senha incorreta.\n");
                return SENHA_INCORRETA;
            }
        }
    }
    // Se chegou aqui, a conta de origem não foi encontrada
    printf("Conta de origem não encontrada.\n");
    return CLIENTE_NAO_ENCONTRADO;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ; // Limpa o buffer de entrada
}