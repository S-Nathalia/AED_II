#ifndef BST_H
#define BST_H


typedef struct no{
  int info;
  struct no *esq;
  struct no *dir;
}No;

void imprimir_elemento(No* elemento);

No* criar_no(int info);

int search_no(No* raiz, int elemento);

No* antecessorPai(No* raiz);

No* antecessor(No* raiz);

No* inserir(No* raiz, int info);

int altura(No* raiz);

void pre_order(No* raiz);

void in_order(No* raiz);

void pos_order(No* raiz);

int maior_elemento(No* raiz);

int menor_elemento(No* raiz);

No* remover(No* raiz, int info);



#endif
