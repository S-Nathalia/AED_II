#ifndef AVL_H
#define AVL_H

typedef struct no {
    int fb;
    int info;
    struct no *esq, *dir;
} No;

void imprimir_elemento(No* no);

No* criar_no(int info);

void pre_order(No* raiz);

No* antecessorPai(No* raiz);

No* antecessor(No* raiz);

No* rotacao_simples_esq(No* pivo);

No* rotacao_simples_dir(No* pivo);

No* casoEspecial_RSD(No* pivo); //rotacao simples a dir

No* casoEspecial_RSE(No* pivo); //rotacao simples a esq

No* rotacao_dupla_esq(No* pivo);

No* rotacao_dupla_dir(No* pivo);

No* rotacionar(No* pivo);

int search_no(No* raiz, int elemento);

No* inserir(No* raiz, int info, int *cresceu);

No* remover(No* raiz, int info, int *diminuiu);

#endif
