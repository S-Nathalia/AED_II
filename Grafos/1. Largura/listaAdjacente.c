#include <stdlib.h>
#include <stdio.h>
#include "listaAdjacente.h"

/*strcut possui a letra do vertice, a lista a ser apontada eh a lista de adj do
mesmo vertice, e seu proximo;
todos os vertice estao em uma lista principal, e cada no dessa lista aponta da
outra lista de seus respectivo vertice... */

Lista* iniciarList(){
    Lista* lista = malloc(sizeof(Lista));
    lista->inicial = NULL;
    return lista;
}

void addList(Lista* lista, char letra){
    Vertice* no = criarVertice(letra);
    if(lista->inicial == NULL){
        lista->inicial = no;
    } else {
        Vertice* cursor = lista->inicial;
        while(cursor->baixo != NULL){
            cursor = cursor->baixo;
        }
        cursor->baixo = no;
    }
}

Lista_Prox* criarListaProx(){
    Lista_Prox* listaAdj = (Lista_Prox*)malloc(sizeof(Lista_Prox));
    listaAdj->inicial = NULL;

    return listaAdj;
}

void adicionarListaProx(Lista_Prox* listaAdj, Vertice* vertice){
    Vertice_Prox* no = criarVerticeProx(vertice);

    if(listaAdj->inicial == NULL){
        listaAdj->inicial = no;
    } else {
        Vertice_Prox* cursor = listaAdj->inicial;
        while(cursor->verticeProx != NULL){
            cursor = cursor->verticeProx;
        }
        cursor->verticeProx = no;
    }
}

Vertice_Prox* criarVerticeProx(Vertice* vertice){
    Vertice_Prox* v = (Vertice_Prox*)malloc(sizeof(Vertice_Prox));
    v->verticeP = vertice;
    v->verticeProx = NULL;

    return v;
}

Vertice* criarVertice(char nome){
    Vertice* v = (Vertice*)malloc(sizeof(Vertice));
    v->adj = criarListaProx();
    v->baixo = NULL;
    v->nome = nome;
    v->cor = -1;
    v->distancia = -1;
    v->pai = NULL;
    v->prox = NULL;

    return v;
}

/* Verifica a existencia do vertice na lista principal, se ele n existe
retornamos 0. */

int verticeExiste(Lista* lista, char x){
    Vertice* cursor = lista->inicial;

    if(cursor == NULL){
        return 0;
    }

    while(cursor != NULL){
        if(cursor->nome == x){
            return 1;
        }
        cursor = cursor->baixo;
    }
    return 0;
}

Vertice* retornarVertice(Lista* lista, char vrt){
    Vertice* cursor = lista->inicial;
    if(cursor == NULL){
        return NULL;
    }
    while(cursor != NULL){
        if(cursor->nome == vrt){
            return cursor;
        }
        cursor = cursor->baixo;
    }
    printf("erro fatal o vertice (%c) nao foi encontrado\n", vrt);
    exit(0);
}

/* Como cada no tem aponta para uma lista de seu respectivo vertice, eh
necessario inicilizar essa lista, nos nós que serao retornados caso existam na
lista principal. Usando a mesma funcao de inserir na lista principal, eh
mandado a lista adj para a qual o nó aponta e mandando um char (e nao um no)
para armazenar na mesma. */

void addAresta(Lista* listaV, char x, char y){
    Vertice* vX, *vY;
    if(verticeExiste(listaV, x) && verticeExiste(listaV, y)){
        Vertice* vX = retornarVertice(listaV, x);
        Vertice* vY = retornarVertice(listaV, y);
        adicionarListaProx(vX->adj, vY);
        adicionarListaProx(vY->adj, vX);
    } else{
        printf("Os vertices %c e %c nao foram encontrados\n", vX->nome, vY->nome);
    }
}

Lista* lerArquivo(Lista* listaV){
    int qntV, qntA;
    char lixo, tempV, x, y;

    FILE* arquivo = fopen("dados.txt", "r");

    if(arquivo != NULL){
        fscanf(arquivo, "%d %d%c", &qntV, &qntA, &lixo);

        for(int i = 0; i < qntV; i++){
            fscanf(arquivo, "%c%c", &tempV, &lixo);
            addList(listaV, tempV);
        }
        for(int k = 0; k < qntA; k++){
            fscanf(arquivo, "%c%c%c", &x, &y, &lixo);
            addAresta(listaV, x, y);
        }
        fclose(arquivo);

    } else{
        printf("arquivo n pode ser aberto. Verifique se ele existe!\n");
    }

    return listaV;
}

//--------------------------------------------------------FILA----------------

Fila* criarFila() {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->primeiroDaFila = NULL;
    fila->ultimoDaFila = NULL;
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


void removerNaFila(Fila* fila) {
    Vertice* v = fila->primeiroDaFila;
    fila->primeiroDaFila = v->prox;
    //return v;
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
