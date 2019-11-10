#include <stdlib.h>
#include <stdio.h>

typedef struct no{
    char vertice;
    struct no* prox;
    struct lista* adj;
}No;

typedef struct lista{
    struct no* inicial;
}Lista;

Lista* initListVertices(){
    Lista* lista = malloc(sizeof(Lista));
    lista->inicial = NULL;
    return lista;
}

void addListVertices(Lista* lista, char letra){
    No* no = (No*) malloc(sizeof(No));
    no->vertice = letra;
    no->adj = initListVertices();

    if(lista->inicial == NULL){
        lista->inicial = no;
    } else {
        No* cursor = lista->inicial;
        while(cursor->prox != NULL){
            cursor = cursor->prox;
        }
        cursor->prox = no;
    }
}

void imprimirListVertices(Lista* listaV){
    if(listaV->inicial == NULL){
        printf("- ");
    } else {
        No* cursor = listaV->inicial;
        while(cursor->prox != NULL){
            printf("%c - ", cursor->vertice);
            cursor = cursor->prox;
        }printf("%c ", cursor->vertice);
    }
}

int verticeExiste(Lista* lista, char x){
    No* cursor = (No*) malloc(sizeof(No));
    cursor = lista->inicial;

    while(cursor != NULL){
        if(cursor->vertice == x){
            return 1;
        }
        cursor = cursor->prox;
    }
    return 0;
}

No* retornarVertice(Lista* lista, char vrt){
    No* cursor = lista->inicial;
    if(cursor == NULL){
        return NULL;
    }
    while(cursor != NULL){
        if(cursor->vertice == vrt){
            return cursor;
        }
        cursor = cursor->prox;
    }
}

void addAresta(Lista* listaV, char x, char y){
    No* vX = (No*) malloc(sizeof(No));
    vX->adj = initListVertices();
    No* vY = (No*) malloc(sizeof(No));
    vY->adj = initListVertices();

    if(verticeExiste(listaV, x)){
        if(verticeExiste(listaV, y)){

            vX = retornarVertice(listaV, x);
            vY = retornarVertice(listaV, y);

            addListVertices(vX->adj, y);
            addListVertices(vY->adj, x);
        }
    } else{
        printf("alguns dos vertices da aresta no arquivo nao existe! Na ligacao %c%c", x, y);
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
            addListVertices(listaV, tempV);
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

void imprimirListaC(Lista* lista){
    No* cursor = NULL;
    No* temp = NULL;

    for(cursor = lista->inicial; cursor != NULL; cursor = cursor->prox){
        printf("%c -> ", cursor->vertice);
        imprimirListVertices(cursor->adj);
        printf("\n");
    }
}


int main(void){
    Lista* lista = initListVertices();
    lista = lerArquivo(lista);
    imprimirListaC(lista);

    return 0;
}
