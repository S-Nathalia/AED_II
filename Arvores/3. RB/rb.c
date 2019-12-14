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

void rotacao_simples_dir(No **raiz, No* no, int simples){
   No *p, *t;

   p = no->esq;
   t = p->dir;

   no->esq = t;
   p->dir = no;

   if(simples){
      p->c = PRETO;
      no->c = VERMELHO;
   }

   if(t != NULL)
   t->pai = no;

   p->pai = no->pai;

   if(eh_raiz(no)){
      *raiz = p;
   } else {
      if(eh_esquerdo(no)){
         no->pai->esq = p;
      } else {
         no->pai->dir = p;
      }
   }
   no->pai = p;
}

void rotacao_simples_esq(No** raiz, No* no, int simples){
   No *p, *t;

   p = no->dir;
   t = p->esq;

   no->dir = t;
   p->esq = no;

   if(simples){
      p->c = PRETO;
      no->c = VERMELHO;
   }

   if(t != NULL){
      t->pai = no;
   }

   p->pai = no->pai;

   if(eh_raiz(no)){
      *raiz = p;
   } else {
      if(eh_esquerdo(no)){
         no->pai->esq = p;
      } else {
         no->pai->dir = p;
      }
   }
   no->pai = p;

}

void rotacao_dupla_esq(No** raiz, No* no){
   rotacao_simples_dir(raiz, no->dir, 0);
   rotacao_simples_esq(raiz, no, 0);

   no->pai->c = PRETO;
   no->c = VERMELHO;
}

void rotacao_dupla_dir(No** raiz, No* no){
   rotacao_simples_esq(raiz, no->esq, 0);
   rotacao_simples_dir(raiz, no, 0);

   no->pai->c = PRETO;
   no->c = VERMELHO;
}

void ajustar(No** raiz, No* no){
   if(eh_raiz(no)){
      no->c = PRETO;
      return;
   } else if(no->pai->c == VERMELHO){
      if(cor(tio(no)) == VERMELHO){ //CASO 1: TIO VERMELHO, BAIXA O PRETO DO AVO
         no->pai->c = PRETO;
         tio(no)->c = PRETO;
         no->pai->pai->c = VERMELHO;
         ajustar(raiz, no->pai->pai);
      } else { //CASO 2: TIO PRETO
         if(eh_esquerdo(no) && eh_esquerdo(no->pai)){ //NO FILHO E NO PAI, FILHOS ESQUERDOS
            rotacao_simples_dir(raiz, no->pai->pai, 1);

         } else if(!eh_esquerdo(no) && !eh_esquerdo(no->pai)){ //NO FILHO E NO PAI, FILHOS DIREITOS
            rotacao_simples_esq(raiz, no->pai->pai, 1);

         } else if(eh_esquerdo(no) && !eh_esquerdo(no->pai)){ //NO FILHO ESQ, PAI DIR
            rotacao_dupla_esq(raiz, no->pai->pai);

         } else if(!eh_esquerdo(no) && eh_esquerdo(no->pai)){ //NO FILHO DIR, PAI ESQ;
            rotacao_dupla_dir(raiz, no->pai->pai);
         }
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

   if(eh_raiz(novo)){
      *raiz = novo;
   } else if(info < pai->info){
      pai->esq = novo;
   } else {
      pai->dir = novo;
   }
   ajustar(raiz, novo);
}
