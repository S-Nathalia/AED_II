#include <stdio.h>
#include <stdlib.h>
//---------------------------------Lista--------------------------------
typedef struct vertice{
    char letra;
    struct lista* adj;
}vertice;
typedef struct no{
    struct vertice* noVertice;
    struct no* prox;

}no;

typedef struct lista{
    struct no* inicial;

}lista;

lista* inicializar(){
    lista* nova = (lista*) malloc(sizeof(lista));
    nova->inicial=NULL;
    return nova;
}

vertice* inicializar_vertice(char letra){
    vertice* ver = (vertice*)malloc(sizeof(vertice));
    ver->letra = letra;
    ver->adj = inicializar();
    return ver;
}
void inserir(lista* lista, vertice* vertice){
    no* novoNo = (no*) malloc(sizeof(no));
    novoNo->noVertice = vertice; //no que vai receber o inteiro e ser adicionado na lista
    if(lista->inicial==NULL){
        lista->inicial = novoNo; //adiciona o primeiro elemento
        novoNo->prox = NULL;
    }else{
        no* cursor = lista->inicial;
        while(cursor->prox!=NULL){
            cursor = cursor->prox;
        }
        novoNo->prox = NULL; // vai ser o ultimo da lista
        cursor->prox = novoNo;

    }
}
void imprimir(lista* lista){
    no* cursor;
    for(cursor=lista->inicial;cursor!=NULL;cursor= cursor->prox){
        printf("%c\n", cursor->noVertice->letra);
    }
}
//---------------------------------Lista--------------------------------


//---------------------------------Grafo--------------------------------
typedef struct grafo{
    int nmrVertices;
    lista* lista_v;
}grafo;


grafo* criarGrafo(int nmrV){
    grafo* g = (grafo*)malloc(sizeof(grafo)); //aloquei memoria para o struct
    g->nmrVertices = nmrV;
    g->lista_v = inicializar();
    return g;
}

void addVertices(grafo* g, char vert){
    vertice* ver = inicializar_vertice(vert);
    inserir(g->lista_v,ver);
}
int buscarVertice(char v, lista* l){
    no* cursor;
    for(cursor = l->inicial;cursor!=NULL; cursor=cursor->prox){
        if(cursor->noVertice->letra == v){
            return 1;
        }
    }
    return 0;
}
vertice* retornarVertice(char v, lista* l){
    no* cursor;
    for(cursor = l->inicial;cursor!=NULL; cursor=cursor->prox){
        if(cursor->noVertice->letra == v){
            return cursor->noVertice;
        }
    }
    return NULL;
}
void addAresta(grafo* gr,char v1,char v2){ //grafo nao dirigido
    no* cursor;
    for(cursor = gr->lista_v->inicial;cursor!=NULL; cursor=cursor->prox){
        if(cursor->noVertice->letra==v1){
            if(buscarVertice(v2,gr->lista_v)){
                vertice* novo = retornarVertice(v2,gr->lista_v);
                inserir(cursor->noVertice->adj, novo);
                inserir(novo->adj, cursor->noVertice);
                break;
            }
        }
    }
}

void imprimirListaADJ(grafo* gr){
    no* cursor;
    no* cursor2;
    for(cursor=gr->lista_v->inicial;cursor!=NULL;cursor= cursor->prox){
        printf("%c-> ", cursor->noVertice->letra);
        for(cursor2=cursor->noVertice->adj->inicial;cursor2!=NULL;cursor2= cursor2->prox){
             printf("%c\t", cursor2->noVertice->letra);
        }
        printf("\n");
    }

}
int main(void){

    FILE *file;
    file = fopen("inf.txt", "r");

    if(file == NULL){
        printf("n foi possivel abrir o arquivo\n");
        exit(0);
    }

    int v,a,i,j;
    fscanf(file, "%d %d", &v,&a); //pegando tamanho dos vertices e arestas
    grafo* gr = criarGrafo(v);

    char vertice,lixo,a1,a2;

    for(i = 0; i<v; i++){ //pegando cada vertice do arquivo e colocando numa lista na posicao de dimensao
        fscanf(file, "%c %c",&lixo,&vertice);
        addVertices(gr,vertice);
    }

    for(j=0; j<a;j++){ //pegando as arestas
        fscanf(file, "%c %c%c",&lixo,&a1,&a2);
        addAresta(gr,a1,a2);
    }
    imprimirListaADJ(gr);
    fclose(file);


}
