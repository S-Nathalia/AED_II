#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

void imprimir_elemento(No* no){
  if(no->c == PRETO)
    printf("\x1b[30m[%d]\x1b[0m", no->info);
  else
    printf("\x1b[31m[%d]\x1b[0m", no->info);
}

No* criar_no(int info){
  No* novo = (No*)malloc(sizeof(No));
  novo->info = info;
  novo->pai = NULL;
  novo->esq = NULL;
  novo->dir = NULL;
  novo->c = VERMELHO;
}

void pre_order(No* raiz){
  if(raiz == NULL)
    return;
  else
    imprimir_elemento(raiz);
    pre_order(raiz->esq);
    pre_order(raiz->dir);
}

int cor(No* no) {
    if(no == NULL || no->c == PRETO)
        return 1;
    else
        return 0;
}

int eh_esquerdo(No* no) {
    if(no == no->pai->esq)
        return 1;
    else
        return 0;
}

int eh_raiz(No* no) {
    if(no->pai == NULL)
        return 1;
    else
        return 0;
}

no* tio (No* n) {
    if(eh_esquerdo(n->pai))
        return n->pai->pai->dir;
    else
        return n->pai->pai->esq;
}

No* rotacao_simples_dir(No* no){

}

No* rotacao_simples_esq(No** raiz, No* no){

}

No* rotacao_dupla_dir_esq(No** raiz, No* no){

}

No* rotacao_dupla_esq_dir(No**, No* no){

}

No* ajustar(No** raiz, No* no){
    if(eh_raiz(no)){
        no->c = PRETO;
        return;
    } else if(no->pai->c == VERMELHO){ //CASO 1 - TIO VERMELHO, BAIXA O PRETO DO AVO
        if(cor(tio(no)) == VERMELHO){
            no->pai->c = PRETO;
            tio(no)->c = PRETO;
            no->pai->pai->c = VERMELHO;
            ajustar(no->pai->pai, raiz);
        }else { //tio preto
            if(eh_esquerdo(n) && eh_esquerdo(no->pai)){
                rotacao_simples_dir(raiz, no->pai->pai);
            } else if(!eh_esquerdo(no) && !eh_esquerdo(no->pai)){
                rotacao_simples_esq(raiz, no->pai->pai);
            } else if(eh_esquerdo(no) && !eh_esquerdo(no->pai)){
                rotacao_dupla_dir_esq(raiz, no->pai->pai);
            }else if(!eh_esquerdo(no) && eh_esquerdo(no->pai)){
                rotacao_dupla_esq_dir(raiz, no->pai->pai);
            }
        }
    }
}

void inserir(No** raiz, int info){

}
