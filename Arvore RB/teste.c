#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int opcao, elemento;
  No* arvore = NULL;


  while(1 == 1) {
    scanf("%d", &opcao);
    switch(opcao) {
      case 1:
        scanf("%d", &elemento);
        arvore = inserir(&arvore, elemento);
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
