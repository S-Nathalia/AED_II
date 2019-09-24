#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


int main(int argc, char*  argv[]) {
	Arvore* arvore = inicializar();
	int opcao;

	while(1 == 1) {
		scanf("%d", &opcao);
		int valor, maior, menor, h;

		switch(opcao) {
			case 1:
				scanf("%d", &valor);
				arvore->raiz = inserir(arvore->raiz, valor);
				break;

			case 2:
				pre_order(arvore->raiz);
				printf("\n");
				break;

			case 3:
				in_order(arvore->raiz);
				//printf("\n");
				break;

			case 4:
				pos_order(arvore->raiz);
				//printf("\n");
				break;

			case 5:
				scanf("%d", &valor);
				arvore->raiz = remover(arvore->raiz, valor);
				break;

			case 6:
				maior = maior_elemento(arvore->raiz);
				printf("%d", maior);
				//printf("\n");
				break;

			case 7:
				menor = menor_elemento(arvore->raiz);
				printf("%d", menor);
				//printf("\n");
				break;

			case 8:
				h = altura(arvore->raiz);
				printf("%d", h);
				//printf("\n");
				break;

			case 9:
				scanf("%d", &valor);
				pai(arvore->raiz, valor);
				//printf("\n");
				break;

			case 10:
				scanf("%d", &valor);
				sucessor(arvore->raiz, valor);
				//printf("\n");
				break;

			case 11:
				scanf("%d", &valor);
				antecessor(arvore->raiz, valor);
				//printf("\n");
				break;

			case 999:
				exit(0);
		}
	}

	return 0;
}
