#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

No* criar_no(int info){
  No* novo = (No*)malloc(sizeof(No));
  novo->info = info;
  novo->pai = NULL;
  novo->esq = NULL;
  novo->dir = NULL;
  novo->c = VERMELHO;
}

void pre_order(No* raiz){
    if(raiz == NULL) ;
    else {
        if(raiz->c == PRETO)
    		printf("\x1b[30m[%d]\x1b[0m", raiz->info);
        else
    		printf("\x1b[31m[%d]\x1b[0m", raiz->info);
        pre_order(raiz->esq);
        pre_order(raiz->dir);
    }
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

No* tio (No* n) {
    if(eh_esquerdo(n->pai))
        return n->pai->pai->dir;
    else
        return n->pai->pai->esq;
}

void rotacao_simples_dir(No* raiz, No* no){
    No *p, *t, *pai;

    pai = no->pai;
    p = no->esq;
    t = p->dir;

    no->c = VERMELHO;
    p->c = PRETO;

    no->esq = t;
    p->dir = no;


    if(t != NULL){
        t->pai = no;
    }

    p->pai = pai;

    if(eh_raiz(no)){
        raiz = p;
    } else {
        if(eh_esquerdo(no)){
            no->pai->esq = p;
        } else {
            no->pai->dir = p;
        }
    }

    no->pai = p;
}

/*No* rotacao_simples_esq(No** raiz, No* no){

}

No* rotacao_dupla_dir_esq(No** raiz, No* no){

}

No* rotacao_dupla_esq_dir(No**, No* no){

}*/

No* ajustar(No* raiz, No* no){
    if(eh_raiz(no)){
        no->c = PRETO;
        return;
    }else if(no->pai->c == VERMELHO){
        if(cor(tio(no)) == VERMELHO){ //CASO 1: TIO VERMELHO, BAIXA O PRETO DO AVO
            no->pai->c = PRETO;
            tio(no)->c = PRETO;
            no->pai->pai->c = VERMELHO;
            ajustar(raiz, no->pai->pai);
        }else { //CASO 2: TIO PRETO
            if(eh_esquerdo(no) && eh_esquerdo(no->pai)){ //NO FILHO E NO PAI, FILHOS ESQUERDOS
                rotacao_simples_dir(raiz, no->pai->pai);

            } /*else if(!eh_esquerdo(no) && !eh_esquerdo(no->pai)){ //NO FILHO E NO PAI, FILHOS DIREITOS
                rotacao_simples_esq(raiz, no->pai->pai);
            } else if(eh_esquerdo(no) && !eh_esquerdo(no->pai)){ //NO FILHO ESQ, PAI DIR
                rotacao_dupla_dir_esq(raiz, no->pai->pai);
            }else if(!eh_esquerdo(no) && eh_esquerdo(no->pai)){ //NO FILHO DIR, PAI ESQ;
                rotacao_dupla_esq_dir(raiz, no->pai->pai);
            }*/ //PRECISA DE UM ELSE?
        }
    }
}

void inserir(No** raiz, int info){ //inserir funciona perfeitamente
    No *temp, *pai, *novo;
    temp  = *raiz;
    pai = NULL;

    while(temp != NULL){
        pai = temp;
        if(info > temp->info){
            temp = temp->dir;
        } else {
            temp = temp->esq;
        }
    }

    novo = criar_no(info);
    novo->pai = pai;

    if(*raiz != NULL){
        if(info > pai->info){
            pai->dir = novo;
        } else {
            pai->esq = novo;
        }
        ajustar(*raiz, novo);
    } else {
        *raiz = novo;
        ajustar(*raiz, novo);
    }
}
