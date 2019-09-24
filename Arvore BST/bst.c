#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void imprimir_elemento(No* elemento){
	printf("[%d]", elemento->info);
}

No* criar_no(int info){
	No* novo = (No*)malloc(sizeof(No));
	novo->pai = NULL;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->info = info;
	return novo;
}

No* buscar_no(No* raiz, int valor){
	if(raiz == NULL){
		return NULL;
	} else{
		while(raiz != NULL && valor != raiz->info){
			if(valor < raiz->info){
				raiz = raiz->esq;
			} else{
				raiz = raiz->dir;
			}
		}
		return raiz;
	}
}

Arvore* inicializar(){
	Arvore* arvore = (Arvore*)malloc(sizeof(Arvore));
	arvore->raiz = NULL;
	return arvore;
}

No* inserir(No* tree, int info){
	No* novo = criar_no(info);
	No* noAtual = tree;

  //Raiz com valor nulo
	if(noAtual == NULL){
		return novo;
	}

	while(noAtual != NULL){
		if(info < noAtual->info){
      //Só entra se chegar no fim do ramo
			if(noAtual->esq == NULL) {
				novo->pai = noAtual;
				noAtual->esq = novo;
				return tree;
			}
			noAtual = noAtual->esq;
      //Caso o valor, a ser adicionado seja maior ou igual que o do noAtual
		}else{
      //Só entra se chegar no fim do ramo
			if(noAtual->dir == NULL) {
				novo->pai = noAtual;
				noAtual->dir = novo;
				return tree;
			}
			noAtual = noAtual->dir;
		}
	}
	return tree;
}

int altura(No* raiz){
	if(raiz == NULL){
		return 0;
	}
	int h_esquerda = altura(raiz->esq);
	int h_direita = altura(raiz->dir);
	if(h_esquerda > h_direita){
		return h_esquerda + 1;
	}
	else{
		return h_direita + 1;
	}
}


void pai(No* no, int info){
	if(no == NULL){
		printf("-1");
	}
	else if(info == no->info){
		printf("%d", no->pai->info);
	}
	else {
		if(info < no->info){
			pai(no->esq, info);
		}else{
			pai(no->dir, info);
		}
	}
}

void pre_order(No* raiz){
	if(raiz == NULL){
		return;
	}
	imprimir_elemento(raiz);
	pre_order(raiz->esq);
	pre_order(raiz->dir);
}


void in_order(No* raiz){
	if(raiz == NULL){
		return;
	}
	in_order(raiz->esq);
	imprimir_elemento(raiz);
	in_order(raiz->dir);
}


void pos_order(No* raiz){
	if(raiz == NULL){
		return;
	}
	pos_order(raiz->esq);
	pos_order(raiz->dir);
	imprimir_elemento(raiz);
}

int maior_elemento(No* raiz){
	No* aux = raiz;
	if(aux == NULL){
		return -1;
	}
	while(aux->dir != NULL){
		aux = aux->dir;
	}
	return aux->info;
}

int menor_elemento(No* raiz){
	No* aux = raiz;
	if(aux == NULL){
		return -1;
	}
	while(aux->esq != NULL){
		aux = aux->esq;
	}
	return aux->info;
}

void antecessor(No* raiz, int info){
	No* aux = buscar_no(raiz, info);
	int menor = menor_elemento(raiz);

	if(raiz == NULL || aux == NULL){
		printf("-1");
		return;
	}
  else if(info == menor){//caso o numero seja o menor elemento, ele n tera antecessor
  	printf("-1");
  }
  else if(aux->esq == NULL){ //caso ele nao tenha filhos a esquerda, entao o antecessor é o pai
  	printf("%d", aux->pai->info);
  }
  else{
  	aux = aux->esq;
  	while(aux->dir != NULL){
  		aux = aux->dir;
  	}
  	printf("%d", aux->info);
  }
}

void sucessor(No* raiz, int info){
	No* aux = buscar_no(raiz, info);
	int maior = maior_elemento(raiz);

	if(raiz == NULL || aux == NULL){
		printf("-1");
		return;
	}
  else if(info == maior){ //caso seja o maior elemento, nesse caso ele nao tem sucessor
  	printf("-1");
  	return;
  }
  else if(aux->dir == NULL){ //caso o no a direita nao tenha no a esquerda, entao ele é o sucessor
  	printf("%d", aux->pai->info);
  }
  else{
  	aux = aux->dir;
  	while(aux->esq != NULL){
  		aux = aux->esq;
  	}
  	printf("%d", aux->info);
  }
}

No* remover(No* raiz, int info){
	No* noAtual = buscar_no(raiz, info);

	if(noAtual == NULL) {
		return raiz;
	}

//clonando o noAtual para o auxiliar
	No* no_aux = noAtual;
	no_aux->pai = noAtual->pai;
	no_aux->esq = noAtual->esq;
	no_aux->dir = noAtual->dir;


	if(raiz == NULL){
		return raiz;

  } else if(noAtual->dir == NULL && noAtual->esq == NULL){ //quando o caso a ser removido é uma folha

    //caso tenha pai
  	if(noAtual->pai != NULL) {
  		if(noAtual->pai->esq != NULL && noAtual->pai->esq == noAtual) {
  			noAtual->pai->esq = NULL;
  		} else {
  			noAtual->pai->dir = NULL;
  		}
  	}
  	free(noAtual);

  } else if(noAtual->dir == NULL && noAtual->esq != NULL){ //quando o removido so tem filho a esquerda

    //se o no for raiz
  	if(no_aux == raiz) {
  		free(raiz);
  		noAtual = noAtual->esq;
  		return noAtual;
  	}

  	noAtual->esq->pai = noAtual->pai;
  	noAtual->pai->esq = noAtual->esq;

  	free(noAtual);

  } else if(noAtual->dir != NULL && noAtual->esq == NULL){ //quando o removido so tem filho a direita

    //se o no a ser removido for raiz
  	if(no_aux == raiz) {
  		free(raiz);
  		noAtual = noAtual->dir;
  		return noAtual;
  	}

  	noAtual->dir->pai = noAtual->pai;
  	noAtual->pai->dir = noAtual->dir;
  	free(noAtual);

  } else {

  	noAtual = noAtual->esq;
  	while(noAtual->dir != NULL){
  		noAtual = noAtual->dir;
  	}

  	noAtual->dir = no_aux->dir;
  	noAtual->dir->pai = noAtual;

  	if(noAtual->esq != NULL && no_aux->pai != raiz) {
  		noAtual->pai->dir = noAtual->esq;
  		noAtual->esq->pai = noAtual->pai;
  		noAtual->esq = no_aux->esq;
  		noAtual->esq->pai = noAtual;
  	}

  	noAtual->pai = no_aux->pai;

  	if(no_aux->pai->esq == no_aux) {
  		noAtual->pai->esq = noAtual;
  	} else {
  		noAtual->pai->dir = noAtual;
  	}

  	free(no_aux);

  	if(noAtual->pai == NULL) {
  		return noAtual;
  	}
  }
  return raiz;
}