
#include <stdlib.h>
#include <stdio.h>

/*strcut possui a letra do vertice, a lista a ser apontada eh a lista de adj do
 mesmo vertice, e seu proximo;
todos os vertice estao em uma lista principal, e cada no dessa lista aponta da
 outra lista de seus respectivo vertice... */


typedef struct no{
    char cor;
    char vertice;
    struct no* prox;
    struct lista* adj;
}No;

typedef struct lista{
    struct no* inicial;
}Lista;

Lista* initList(){
    Lista* lista = malloc(sizeof(Lista));
    lista->inicial = NULL;
    return lista;
}

void addList(Lista* lista, char letra){
    No* no = (No*) malloc(sizeof(No));
    no->vertice = letra;
    no->adj = initList();

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

void imprimirList(Lista* listaV){
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

/* Verifica a existencia do vertice na lista principal, se ele n existe
 retornamos 0. */

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

/* Como cada no tem aponta para uma lista de seu respectivo vertice, eh
 necessario inicilizar essa lista, nos nós que serao retornados caso existam na
  lista principal. Usando a mesma funcao de inserir na lista principal, eh
   mandado a lista adj para a qual o nó aponta e mandando um char (e nao um no)
    para armazenar na mesma. */

void addAresta(Lista* listaV, char x, char y){
    No* vX = (No*) malloc(sizeof(No));
    vX->adj = initList();

    if(verticeExiste(listaV, x)){
        vX = retornarVertice(listaV, x);
        addList(vX->adj, y);
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

void imprimirListaC(Lista* lista){
    No* cursor = NULL;
    No* temp = NULL;

    for(cursor = lista->inicial; cursor != NULL; cursor = cursor->prox){
        /* imprimi o primeiro vertice da lista principal... */
        printf("%c -> ", cursor->vertice);
        /* e seus respectivos nós conectados. */
        imprimirList(cursor->adj);
        printf("\n");
    }
}
