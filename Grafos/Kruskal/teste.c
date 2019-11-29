#include "kruskal.h"

int main(int argv, char *argc[]){
Grafo *grafoI = inicializarGrafo(0, 1);
Grafo *grafoF = inicializarGrafo(0, 1);
int i;
int flag = 0;
    for(i = 1; i < argv; i++){
        if(strcmp(argc[i], "-h") == 0){
            printf("-h			: mostra o help \
			\n-o <arquivo>		: redireciona a saida para o arquivo \
			\n-f <arquivo>		: indica o ‘‘arquivo’’ que contém o grafo de entrada \
			\n-s		        : mostra a solução (em ordem crescente) \n\n");
        }

        if(strcmp(argc[i], "-f")== 0){
            receberArquivo(argc[i+1], grafoI);
            kruskal(grafoI, grafoF);
            flag = 1;
        }

        if(strcmp(argc[i], "-o") == 0){
        	FILE *arquivo = fopen(argc[i+1], "w");
        	if (arquivo == NULL){
        		printf("Erro de saida\n");
        	}
        	else{
        		escreverArquivo(arquivo, grafoF);
        	}
            fclose(arquivo);
            flag = 1;
        }

        if(strcmp(argc[i], "-s")== 0){
            imprimirGrafo(grafoF);
            flag = 0;
        }
    }

    if (flag == 1){
        Aresta *aux = grafoF->arestas;
        int peso = 0;

        while(aux != NULL){
            peso += aux -> peso;
            aux = aux->prox;
        }

        printf("%d\n", peso);
    }

    return 0;
}
