#include <stdio.h>
#include <stdlib.h>

int ** criarMatrizPreenchida(int vertice){
    int ** matriz;
    int i,j;

    matriz = (int**)malloc(sizeof(int*)*vertice);

    for(i=0;i<vertice;i++){
        matriz[i] = (int*) malloc(sizeof(int)*vertice);
    }

    //preencher

    for(i=0;i<vertice;i++){
        for(j=0;j<vertice;j++){
            if(i==j){
               matriz[i][j]=1;
            }else{
                matriz[i][j]=0;
            }
        }
    }
    return matriz;
}
void lerMatriz(int vertice, int **matriz){
    int i, j;
    for(i=0;i<vertice;i++){
        printf("\n");
        for(j=0;j<vertice;j++){
            printf(" %d ", matriz[i][j]);
        }
    }
}
void addArestaNaMatriz(char a1,char a2,int** matriz,char vertices[],int v){
    int i, p1,p2;

    for(i=0;i<v;i++){
        if(a1==vertices[i]){
            p1=i;
        }
        if(a2==vertices[i]){
            p2=i;
        }
    }

    matriz[p1][p2] = 1;
    matriz[p2][p1] = 1;

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

    char vertices[v]; //declarando tamanho do vetor de vertices

    char vertice,lixo,a1,a2;

    int **matriz=criarMatrizPreenchida(v);
    lerMatriz(v,matriz);

    for(i = 0; i<v; i++){ //pegando cada vertice do arquivo e colocando no vetor vertices
        fscanf(file, "%c %c",&lixo,&vertice);
        vertices[i] = vertice;
    }
    for(j=0; j<a;j++){ //pegando as arestas e colocando na matriz
       fscanf(file, "%c %c%c",&lixo,&a1,&a2);
       addArestaNaMatriz(a1,a2,matriz,vertices,v);
    }
    printf("\n%d vertices %d arestas\n", v,a);

    for(i = 0; i<v; i++){
        printf("v[%d]: %c\t ",i,vertices[i]);
    }

    lerMatriz(v,matriz);

    fclose(file);


}
