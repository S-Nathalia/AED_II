#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char *argv[]) {
   No* arvore = NULL;
   int opcao, elemento;
   int cresceu, diminuiu;

   while(1 == 1) {
      scanf("%d", &opcao);
      switch(opcao) {

         case 1:
         scanf("%d", &elemento);
         arvore = inserir(arvore, elemento, &cresceu);
         break;
         case 2:
         pre_order(arvore);
         printf("\n");
         break;
         case 3:
         scanf("%d", &elemento);
         arvore = remover(arvore, elemento, &diminuiu);
         break;
         case 999:
         exit(0);
      }
   }
}
