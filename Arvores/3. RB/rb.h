#ifndef RB_H
#define RB_H

enum cor {VERMELHO, PRETO};

typedef struct no{
  enum cor c;
  int info;
  struct no *pai, *esq, *dir;
} No;

//void imprimir_elemento(No* no);

No* criar_no(int info);

void pre_order(No* raiz);

int cor(No* no);

int eh_esquerdo(No* no);

int eh_raiz(No* no);

No* tio(No* n);

void rotacao_simples_dir(No** raiz, No* no, int simples);

void rotacao_simples_esq(No** raiz, No* no, int simples);

void rotacao_dupla_dir(No** raiz, No* no);

void rotacao_dupla_esq(No** raiz, No* no);

void ajustar(No** raiz, No* no);

void inserir(No** raiz, int info);

#endif
