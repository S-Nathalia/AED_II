#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
    char nome;
    struct vertice* prox;
} Vertice;


typedef struct fila {
    struct vertice* primeiroDaFila;
    struct vertice* ultimoDaFila;
} Fila;

Fila* criarFila() {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->primeiroDaFila = NULL;
    fila->ultimoDaFila = NULL;
}


Vertice* criarVertice(char nome) {
    Vertice* v = (Vertice*) malloc(sizeof(Vertice));
    v->nome = nome;
    v->prox = NULL;
    return v;
}

void addNaFila(Fila* fila, Vertice* v) {
    if(fila->primeiroDaFila == NULL) {
        fila->ultimoDaFila = v;
        fila->primeiroDaFila = v;
    } else {
        fila->ultimoDaFila->prox = v;
        fila->ultimoDaFila = v;
    }
}


Vertice* removerNaFila(Fila* fila) {
    Vertice* v = fila->primeiroDaFila;
    fila->primeiroDaFila = v->prox;
    return v;
}

void imprimirFila(Fila* fila) {
    if(fila->primeiroDaFila == NULL) {
        printf("Fila nula!");
    } else {
        Vertice* v = fila->primeiroDaFila;
        while(v != NULL) {
            printf("%c - ", v->nome);
            v = v->prox;
        }
    }
    printf("\n");

}


void main() {

    // Cria a fila
    Fila* fila = criarFila();

    // Add alguns nós nela
    Vertice* v = criarVertice('a');
    addNaFila(fila, v);

    v = criarVertice('b');
    addNaFila(fila, v);

    v = criarVertice('c');
    addNaFila(fila, v);

    v = criarVertice('d');
    addNaFila(fila, v);

    // Imprime fila com nos adicionados
    imprimirFila(fila);

    // Remove da fila
    removerNaFila(fila);

    // Imprime com o no removido
    imprimirFila(fila);

}
