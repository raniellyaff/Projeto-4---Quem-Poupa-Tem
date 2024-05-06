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
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");

    scanf("%d", &opcao);
    clearBuffer();
    switch (opcao){
      case 1:
      resultado = criar(clientes, &pos);
      break;
    }
  } while (opcao != 0);
}