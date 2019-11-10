/*
* Implementação de grafos não dirigidos utilizando uma
* matriz de adjacências.
*/

#include <stdlib.h>
#include<stdio.h>

typedef struct grafo{
  int vertice;    /* quantidade total de vertices */
  int **matriz;  /* Matriz (a ser alocada dinamicamente) */
  char *mapa;
} Grafo;

/*Cria uma matriz quadrada, com a diagonal 1, e o restante 0. */

Grafo* criarMatriz(int vertices, Grafo *grafo){
  grafo = malloc(sizeof(Grafo));
  grafo->vertice = vertices;
  grafo->mapa = (char*)malloc(sizeof(char) * vertices);
  grafo->matriz = (int**) malloc(vertices * sizeof(int*));

  for(int k = 0; k < vertices; k++){
    grafo->matriz[k] = (int*) malloc(vertices * sizeof(int));
  }

  for(int i = 0; i < vertices; i++){
    for(int j = 0; j < vertices; j++){
      if(i != j){
        grafo->matriz[i][j] = 0;
      } else{
        grafo->matriz[i][j] = 1;
      }
    }
  }
  return grafo;
}

Grafo* addAresta(Grafo* grafo, char x, char y){

  /*Descrição:
  x e y serão, respectivamente, as coordenadas em que teremos uma arestas.
  Se x seŕá igual ao novo índice, a variavel coluna terá  seu valor, o mesmo
  para variavel linha (ou vice-versa). Logo após a atribuição, como o grafo nao
  eh direcionado, as posiçoes x y e yx serão iguais, ambas contendo 1 em sua
  posiçao. */

  int posLinha;
  int posColuna;
  for(int n = 0; n < grafo->vertice; n++){
    if(x == grafo->mapa[n]){
      posLinha = n;
    }
    if(y == grafo->mapa[n]){
      posColuna = n;
    }
  }
  grafo->matriz[posLinha][posColuna] = 1;
  grafo->matriz[posColuna][posLinha] = 1;

  return grafo;
}

/* TODO: imprimir de forma que exiba a qual vertice a coluna linha se refere.*/

void imprimirMatriz(Grafo* grafo){
  for(int i = 0; i < grafo->vertice; i++){
    for(int j = 0; j < grafo->vertice; j++){
      printf("%d  ", grafo->matriz[i][j]);
    }
    printf("\n");
  }
}

/*Abre o arquivo em modo read, e irá lendo linha por linha
a variavel lixo, eh onde está sendo colocado o \n.*/

Grafo* lerArquivo(Grafo* grafo){
  int vertices, arestas;
  char lixo, x, y, temp;

  FILE* arquivo = fopen("dados.txt", "r");

  if(arquivo != NULL){
    fscanf(arquivo, "%d %d", &vertices, &arestas);
    grafo = criarMatriz(vertices, grafo);
    for(int i = 0; i < vertices; i++){
      fscanf(arquivo, "%c%c", &lixo, &temp);
      grafo->mapa[i] = temp;//erro aqui

    }
    for(int k = 0; k < arestas; k++){
      fscanf(arquivo, "%c%c%c", &lixo, &x, &y);
      grafo = addAresta(grafo, x, y);
    }
  }
  return grafo;

  fclose(arquivo);
}


int main(){
  Grafo* grafo;
  grafo = lerArquivo(grafo);
  imprimirMatriz(grafo);
  return 0;
}
