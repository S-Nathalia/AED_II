#ifndef BST_H
#define BST_H


typedef struct no{
  int info;
  struct no *pai;
  struct no *esq;
  struct no *dir;
}No;


typedef struct arvore{
  No* raiz;
}Arvore;


void imprimir_elemento(No* elemento);

No* criar_no(int info);

No* buscar_no(No* raiz, int valor);

Arvore* inicializar();

No* inserir(No* tree, int info);

int altura(No* raiz);

void pai(No* raiz, int info);

void pre_order(No* raiz);

void in_order(No* raiz);

void pos_order(No* raiz);

int maior_elemento(No* raiz);

int menor_elemento(No* raiz);

void antecessor(No* raiz, int info);

void sucessor(No* raiz, int info);

No* remover(No* raiz, int info);



#endif
