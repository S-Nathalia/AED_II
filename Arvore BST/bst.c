#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void imprimir_elemento(No* elemento){
	printf("[%d]", elemento->info);
}

No* criar_no(int info){
	No* novo = (No*)malloc(sizeof(No));
	novo->esq = NULL;
	novo->dir = NULL;
	novo->info = info;
	return novo;
}

int search_no(No* raiz, int elemento){ //procura se o no existe na arvore;
  while(raiz != NULL){
    if(raiz->info == elemento) return 1;
    if(elemento > raiz->info){
      raiz = raiz->dir;
    } else {
      raiz = raiz->esq;
    }
  }
  return 0;
}

No* antecessorPai(No* raiz) {
  No* aux_pai = raiz;
  No* aux = raiz->esq;
  while(aux->dir != NULL){
    aux_pai = aux;
    aux = aux->dir;
  }
  return aux_pai;
}

No* antecessor(No* raiz){ //quando chegar aqui o no obrigatoriamente tera dois filhos.
  No* no_pai = antecessorPai(raiz);
  if(no_pai == raiz) {
    return antecessorPai(raiz)->esq; //se o no pai for igual a raiz da arvore, entao o antecessor sera
                                        //serao no a esquerda
  } else {
    return antecessorPai(raiz)->dir;
  }
}

No* inserir(No* raiz, int info){
	No* novo = criar_no(info);

    if(raiz == NULL){
        return novo;

    } else {
        if(info > raiz->info){
            raiz->dir = inserir(raiz->dir, info);
        } else {
            raiz->esq = inserir(raiz->esq, info);
        }
        return raiz;
    }
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

No* remover(No* raiz, int info){
	if(raiz == NULL){
        return NULL;
    }
    else if(!search_no(raiz, info)){//quando o no nao  na arvore
        return raiz;
    }
    else if(info > raiz->info){
        raiz->dir = remover(raiz->dir, info);

    } else if(info < raiz->info){

        raiz->esq = remover(raiz->esq, info);
    } else {
        No* no_aux = raiz;
        if(raiz->esq == NULL && raiz->dir == NULL){ //Sem filhos
            free(no_aux);
            raiz = NULL;

        } else if(raiz->esq != NULL && raiz->dir == NULL){ //Unico filho a esquerda
            raiz = raiz->esq;
            free(no_aux);

        } else if(raiz->esq == NULL && raiz->dir != NULL){ //unico filho a direita
            raiz = raiz->dir;
            free(no_aux);

        } else { //Dois filhos
            No* predecessor = antecessor(raiz);
            raiz->info = predecessor->info;
            raiz->esq = remover(raiz->esq, predecessor->info);

        }
    }
    return raiz;
}
