#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void imprimir_elemento(No* no){
   printf("[%i,%i]", no->info, no->fb);
}

No* criar_no(int info){
   No* novo = (No*)malloc(sizeof(No));
   novo->info = info;
   novo->esq = NULL;
   novo->dir = NULL;
   novo->fb = 0;

   return novo;
}

void pre_order(No* raiz){
   if(raiz == NULL)
   return;

   imprimir_elemento(raiz);
   pre_order(raiz->esq);
   pre_order(raiz->dir);
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

No* rotacao_simples_dir(No* pivo){
   No* u = pivo->esq;

   pivo->esq = u->dir;
   u->dir = pivo;

   u->fb = 0;
   pivo->fb = 0;

   return u;
}

No* rotacao_simples_esq(No* pivo){

   pivo->dir = u->esq;
   u->esq = pivo;

   u->fb = 0;
   pivo->fb = 0;

   return u;
}

No* casoEspecial_RSE(No* pivo){ //caso especial, quando na remocao existe um no com fb de 0
   No* u = pivo->dir;              // e seu pai tem fb 2;
   No* u = pivo->dir;

   pivo->dir = u->esq;
   u->esq = pivo;

   u->fb = -1;
   pivo->fb = 1;

   return u;

}

No* casoEspecial_RSD(No* pivo){ // caso simetrico ao de cima;
   No* u = pivo->esq;

   pivo->esq = u->dir;
   u->dir = pivo;

   u->fb = 1;
   pivo->fb = -1;

   return u;
}

No* rotacao_dupla_dir(No* pivo){
   No* w = pivo->esq;
   No* n = w->dir;

   w->dir = n->esq;
   n->esq = w;  //primeira rotacao

   pivo->esq = n->dir;
   n->dir = pivo; //segunda rotacao

   if(n->fb == 1){
      w->fb == -1;
   } else {
      w->fb = 0;
   }

   if(n->fb == -1){ //verificando no n para mudar os fb dos demais
      pivo->fb = 1;
   } else {
      pivo->fb = 0;
   }
   return n;
}

No* rotacao_dupla_esq(No* pivo){
   No* w = pivo->dir;
   No* n = w->esq;

   w->esq = n->dir;
   n->dir = w; //primeira rotacao

   pivo->dir = n->esq;
   n->esq = pivo; //segunda rotacao

   if(n->fb == -1){ //verificando no n para mudar os fb dos demais
      w->fb = 1;
   } else {
      w->fb = 0;
   }

   if(n->fb == 1){
      pivo->fb = -1;
   } else {
      pivo->fb = 0;
   }
   return n;
}

No* rotacionar(No* pivo){
   if(pivo->fb == -2 && pivo->esq->fb == -1){
      return rotacao_simples_dir(pivo);
   }
   else if(pivo->fb == 2 && pivo->dir->fb == 1){
      return rotacao_simples_esq(pivo);
   }
   else if(pivo->fb == -2 && pivo->esq->fb == 1){
      return rotacao_dupla_dir(pivo);
   }
   else if(pivo->fb == 2 && pivo->dir->fb == -1){
      return rotacao_dupla_esq(pivo);
   }
   else if(pivo->fb == -2 && pivo->esq->fb == 0){ //caso especial
      return casoEspecial_RSD(pivo);
   }
   else if(pivo->fb == 2 && pivo->dir->fb == 0){ //caso especial 2
      return casoEspecial_RSE(pivo);
   }
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

No* inserir(No* raiz, int info, int *cresceu){
   No* novo = criar_no(info);

   if(raiz == NULL){
      *cresceu = 1;
      return novo;

   } else {
      if(info > raiz->info){
         raiz->dir = inserir(raiz->dir, info, cresceu);
         if(*cresceu) {
            switch(raiz->fb) {
               case -1:
               raiz->fb = 0;
               *cresceu = 0;
               break;
               case 0:
               raiz->fb = 1;
               *cresceu = 1;
               break;
               case 1:
               raiz->fb = 2;
               *cresceu = 0;
               return rotacionar(raiz);
               break;
            }

         }
      } else {
         raiz->esq = inserir(raiz->esq, info, cresceu);
         if(*cresceu) {
            switch(raiz->fb) {
               case -1:
               raiz->fb = -2;
               *cresceu = 0;
               return rotacionar(raiz);
               break;
               case 0:
               raiz->fb = -1;
               *cresceu = 1;
               break;
               case 1:
               raiz->fb = 0;
               *cresceu = 0;
               break;
            }
         }
      }
      return raiz;
   }
}

No* remover(No* raiz, int info, int *diminuiu){
   if(raiz == NULL){
      return NULL;
   }
   else if(!search_no(raiz, info)){//quando o no nao  na arvore
      return raiz;
   }
   else if(info > raiz->info){
      raiz->dir = remover(raiz->dir, info, diminuiu);
      if(*diminuiu){
         switch (raiz->fb){
            case -1:
            raiz->fb = -2;
            if(raiz->esq->fb == 0)
            *diminuiu = 0;
            else
            *diminuiu = 1;
            return rotacionar(raiz);
            break;
            case 0:
            raiz->fb = -1;
            *diminuiu = 0;
            break;
            case 1:
            raiz->fb = 0;
            *diminuiu = 1;
            break;
         }
      }
   } else if(info < raiz->info){
      raiz->esq = remover(raiz->esq, info, diminuiu);
      if(*diminuiu){
         switch (raiz->fb) {
            case -1:
            raiz->fb = 0;
            *diminuiu = 1;
            break;
            case 0:
            raiz->fb = 1;
            *diminuiu = 0;
            break;
            case 1:
            raiz->fb = 2;
            if(raiz->dir->fb == 0)
            *diminuiu = 0;
            else
            *diminuiu = 1;
            return rotacionar(raiz);
            break;
         }
      }
   } else {
      No* no_aux = raiz;
      *diminuiu = 1;

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
         raiz->esq = remover(raiz->esq, predecessor->info, diminuiu);

         if(*diminuiu){
            switch (raiz->fb) {
               case -1:
               raiz->fb = 0;
               *diminuiu = 1;
               break;
               case 0:
               raiz->fb = 1;
               *diminuiu = 0;
               break;
               case 1:
               raiz->fb = 2; //antes de mandar para rotacao, nesse caso preciso saber se o no tem filhos, pois nesse caso a arvore ira
               if(raiz->dir == 0) //diminuir ou nao
               *diminuiu = 0;
               else
               *diminuiu = 1;
               return rotacionar(raiz);
               break;
            }
         }
      }
   }
   return raiz;
}
