#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int opcao, info;
  No* arvore = NULL;

  while(1 == 1) {
    scanf("%d", &opcao);

    switch(opcao) {
      case 1:
        scanf("%d", &info);
        inserir(&arvore, info);
        break;

      case 2:
        pre_order(arvore);
        printf("\n");
        break;

      case 999:
        exit(0);
    }
  }
}
