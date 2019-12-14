#include <stdlib.h>
#include <stdio.h>
#include "listaAdjacente.h"

int tempo = 0;

void pintarBranco(Lista* grafo){
    Vertice* u = NULL;

    if(grafo != NULL)
        for(u = grafo->inicial; u != NULL; u = u->baixo){
            u->cor = 0;
            u->pai = NULL;
        }
}

void visitaP(Vertice* u){
    u->cor = 1;
    tempo = tempo + 1;
    u->tempo[0] = tempo;

    Vertice_Prox* v = u->adj->inicial;
    while(v != NULL){
        if(v->verticePrincipal->cor == 0){
            v->verticePrincipal->pai = u;
            return visitaP(v->verticePrincipal);
        }
        v = v->verticeProx;
    }
    u->cor = 2;
    tempo = tempo + 1;
    u->tempo[1] = tempo;
}

void buscaProfundidade(Lista* grafo){
    lerArquivo(grafo);
    pintarBranco(grafo);

    Vertice* u = grafo->inicial;

    for(u = u; u != NULL; u = u->baixo){
        if(u->cor == 0){
            return visitaP(u);
        }
    }
}

int main(void){
    Lista* grafo = iniciarList(grafo);
    buscaProfundidade(grafo);
    imprimirLista(grafo);
    listarVertices(grafo);
}
