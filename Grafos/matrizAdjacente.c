#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criarMatriz(){
   FILE *dados;

   dados = fopen("arquivo.txt", "r");

   fclose(dados);

   return 0;
}
