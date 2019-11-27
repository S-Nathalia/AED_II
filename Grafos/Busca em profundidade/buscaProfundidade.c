#include <stdlib.h>
#include <stdio.h>
#include "listaAdjacente.h"

int tempo = 0;

void dfs(Lista* lista){
    lista = lerArquivo(lista);

    No* aux =  NULL;
    No* cursor = NULL;

    for(aux = lista->inicial; aux != NULL; aux = aux->prox){
        for(cursor = aux->adj->inicial; cursor != NULL; cursor = cursor->prox){
            aux->cor = BRANCO;
            aux->pai = NULL;
            cursor->cor = BRANCO;
            cursor->pai = NULL;
            tempo = 0;
        }
    }
    No* u;
    for(u = lista->inicial; u != NULL; u = u->prox){
        if(u->cor == BRANCO){
            dfsVisit(u);
        }
    }
}

No* dfsVisit(No* u){
    u->cor = CINZA;
    tempo = tempo + 1;
    u->tempo[0] = tempo;
    for(No* v = u->adj->inicial; v != NULL; v = v->prox){
        if(u->cor = BRANCO){
            v->pai = u;
            return dfsVisit(v);
        }
    }
    u->cor = PRETO;
    tempo = tempo + 1;
    u->tempo[1] = tempo;
}

int main(void){
    Lista* lista = initList();
    dfs(lista);
    return 0;
}
