#ifndef LISTAADJACENTE_H
#define LISTAADJACENTE_H

typedef struct vertice{
    int cor;
    char nome;
    int distancia;
    struct vertice* pai;
    struct lista_prox* adj;
    struct vertice* baixo;
    struct vertice* prox;
} Vertice;

typedef struct lista{
    struct vertice* inicial;
}Lista;

typedef struct lista_prox{
    struct vertice_prox* inicial;
}Lista_Prox;

typedef struct vertice_prox{
    struct vertice* verticeP;
    struct vertice_prox* verticeProx;
} Vertice_Prox;

typedef struct fila {
    struct vertice* primeiroDaFila;
    struct vertice* ultimoDaFila;
} Fila;

Lista_Prox* criarListaProx();

void adicionarListaProx(Lista_Prox* listaAdj, Vertice* vertice);

Vertice_Prox* criarVerticeProx(Vertice* vertice);

Lista* iniciarList();

void addList(Lista* lista, char letra);

Vertice* criarVertice(char nome);

int verticeExiste(Lista* lista, char x);

Vertice* retornarVertice(Lista* lista, char vrt);

void addAresta(Lista* listaV, char x, char y);

Lista* lerArquivo(Lista* listaV);

void addNaFila(Fila* fila, Vertice* v);

void removerNaFila(Fila* fila);

Fila* criarFila();

void imprimirFila(Fila* fila);

#endif
