#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unordered_set>
#include <iostream>
#include <vector>

using namespace std;

typedef struct aresta{
    struct vertice* verticeOrigem;
    struct vertice* verticeDestino;
    struct aresta* proxAresta;
    int peso;
}Aresta;

typedef struct vertice{
    char nome;
    struct vertice* proxVertice;
}Vertice;

typedef struct grafo{
    int ponderado;
    int qntV;
    int qntA;
    struct vertice* verticeInicial;
    struct aresta* arestaInicial;
}Grafo;

int ponderado(Grafo* grafo);

Grafo* iniciarGrafo(int ponderado);

Vertice* criarVertice(char nome);

void adicionarVertice(Grafo* grafo, char nome);

Vertice* retornarVertice(Vertice* verticeI, char nome);

Aresta* criarAresta(Vertice* origem, Vertice* destino, int peso, Grafo* grafo);

void adicionarAresta(Grafo* grafo, char origem, char destino, int peso);

bool verticeExiste(Grafo* grafo, char nome);

void lerArquivo(Grafo* grafo);

void imprimirGrafo(Grafo* grafo);

Grafo* kruskal(Grafo* grafo);

vector<char> substituir_no_Vetor(vector<char> vetor, char x, char y);

#endif //KRUSKAL_H
