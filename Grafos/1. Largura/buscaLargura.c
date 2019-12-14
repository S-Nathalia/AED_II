#include <stdlib.h>
#include <stdio.h>
#include "listaAdjacente.h"

void iniciarVertices(Lista* grafo){
    if(grafo->inicial == NULL){
        printf("Grafo nulo em iniciar branco \n");
        return;
    }
    Vertice* v = NULL;
    for(v = grafo->inicial; v != NULL; v = v->baixo){
        v->cor = 0;
        v->distancia = -1;
        v->pai = NULL;
    }
}

void buscaLargura(Lista* grafo){
    Fila* fila = criarFila();
    if(fila == NULL){
        printf("fila nula \n");
    }
    iniciarVertices(grafo);

    Vertice* s = grafo->inicial;
    s->cor = 1;
    s->distancia = 0;
    s->pai = NULL;

    addNaFila(fila, s);
    imprimirFila(fila);
    Vertice_Prox* x = s->adj->inicial;

    for(x = x; x != NULL; x = x->verticeProx){
        x->verticeP->cor = 1;
        x->verticeP->distancia = s->distancia + 1;
        x->verticeP->pai = s;
        addNaFila(fila, x->verticeP);
    }
    s->cor = 2;
    removerNaFila(fila);
    imprimirFila(fila);

    Vertice* no = fila->ultimoDaFila;
    Vertice_Prox* cursor;
    while(fila != NULL){
        for(cursor = fila->ultimoDaFila->adj->inicial; cursor != NULL; cursor = cursor->verticeProx){
            if(cursor->verticeP->cor == 0){
                cursor->verticeP->cor = 1;
                cursor->verticeP->distancia = s->distancia +1;
                cursor->verticeP->pai = no;
                addNaFila(fila, cursor->verticeP);
            }
        }
        no->cor = 2;
        removerNaFila(fila);
        no = no->prox;
    }

}

void imprimir(Lista* grafo){
    if(grafo->inicial == NULL){
        printf("Grafo nulo \n");
        return;
    }
    Vertice* v = NULL;
    for(v = grafo->inicial; v != NULL; v = v->baixo){
        printf("vertice: %c | cor: %d | pai: %c | distancia : %d \n", v->nome, v->cor, v->pai->nome, v->distancia);
    }
}
int main(){
    Lista* grafo = iniciarList();
    grafo = lerArquivo(grafo);
    buscaLargura(grafo);
    imprimir(grafo);

}
