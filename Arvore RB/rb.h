#ifndef RB_H
#define RB_H

enum cor {VERMELHO, PRETO};

typedef struct no{
  enum cor c;
  int info;
  struct no *pai, *esq, *dir;
} No;

void imprimir_elemento(No* no);

No* criar_no(int info);

void pre_order(No* raiz);

#endif
