#include <stdio.h>
#include "banco.h"

int main() {
  Cliente clientes[TOTAL];
  int pos = 0;
  int opcao;
  ERROS resultado;

  do {
    printf("\nMenu Principal\n");
    printf("1 - Criar conta\n");
    printf("2 - Deletar conta\n");
    printf("3 - Listar contas\n");
    printf("4 - Débito\n");
    printf("5 - Depósito\n");
    printf("6 - PIX\n");
    printf("7 - Extrato\n");
    printf("8 - Salvar em Binário\n");
    printf("9 - Carregar de Binário\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");

    scanf("%d", &opcao);
    clearBuffer();
    switch (opcao){
      case 1:
        resultado = criar(clientes, &pos);
        break;
      case 2: 
        resultado = deletar(clientes, &pos);
        break;
      case 3:
        resultado = listar(clientes, &pos);
        break;
      case 4:
        resultado = debito(clientes, &pos);
        break;
      case 5:
        resultado = deposito(clientes, &pos);
        break;
      case 6:
        resultado = pix(clientes, &pos);
        break;
      case 7:
        resultado = extrato(clientes, &pos);
        break;
      case 8:
        resultado = salvarbinario(clientes, pos);
        break;
      case 9:
        resultado = carregarbinario(clientes, &pos);
        break;
      default:
        printf("Opção inválida!");
        break;
    }
  } while (opcao != 0);
}