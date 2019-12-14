#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


int main(int argc, char*  argv[]) {
	int opcao;
	No* arvore = NULL;

	while(1 == 1) {
		scanf("%d", &opcao);
		int valor, maior, menor, h;

		switch(opcao) {
			case 1:
				scanf("%d", &valor);
				arvore = inserir(arvore, valor);
				break;

			case 2:
				pre_order(arvore);
				printf("\n");
				break;

			case 3:
				in_order(arvore);
				printf("\n");
				break;

			case 4:
				pos_order(arvore);
				printf("\n");
				break;

			case 5:
				scanf("%d", &valor);
				arvore = remover(arvore, valor);
				break;

			case 6:
				maior = maior_elemento(arvore);
				printf("%d", maior);
				printf("\n");
				break;

			case 7:
				menor = menor_elemento(arvore);
				printf("%d", menor);
				printf("\n");
				break;

			case 8:
				h = altura(arvore);
				printf("%d", h);
				printf("\n");
				break;

			case 999:
				exit(0);
		}
	}

	return 0;
}
