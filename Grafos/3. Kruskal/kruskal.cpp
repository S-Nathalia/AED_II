#include "kruskal.h"

Grafo* iniciarGrafo(int ponderado){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->arestaInicial = NULL;
    grafo->verticeInicial = NULL;
    grafo->ponderado = ponderado;
    grafo->qntA = 0;
    grafo->qntV = 0;

    return grafo;
}

Aresta* criarAresta(Vertice* origem, Vertice* destino, int peso, Grafo* grafo){
    Aresta* aresta = (Aresta*)malloc(sizeof(Aresta));
    aresta->verticeOrigem = origem;
    aresta->verticeDestino = destino;
    aresta->proxAresta = NULL;

    if(grafo->ponderado == 1){
        aresta->peso = peso;
    } else {
        aresta->peso = 0;
    }
    return aresta;
}

void adicionarAresta(Grafo* grafo, char origem, char destino, int peso){
    Vertice* V_origem = retornarVertice(grafo->verticeInicial, origem);
    Vertice* V_destino = retornarVertice(grafo->verticeInicial, destino);
    Aresta* aresta = criarAresta(V_origem, V_destino, peso, grafo);

    if(grafo->arestaInicial == NULL){
        grafo->arestaInicial = aresta;
    } else {
        Aresta* cursor = grafo->arestaInicial;

        while(cursor->proxAresta != NULL && cursor->proxAresta->peso < peso){
            cursor = cursor->proxAresta;
        }
        if(cursor->proxAresta == NULL){
            if(grafo->arestaInicial == cursor && cursor->peso > peso){
                aresta->proxAresta = cursor;
                grafo->arestaInicial = aresta;
            } else {
                cursor->proxAresta = aresta;
            }
        } else {
            Aresta* aux = cursor->proxAresta;
            cursor->proxAresta = aresta;
            aresta->proxAresta = aux;
        }
    }
    grafo->qntA += 1;
}

Vertice* criarVertice(char nome){
    Vertice* vertice = (Vertice*)malloc(sizeof(Vertice));
    vertice->nome = nome;
    vertice->proxVertice = NULL;

    return vertice;
}

bool verticeExiste(Grafo* grafo, char nome){
    if(grafo->verticeInicial == NULL){
        return false;
    }
    Vertice* cursor = grafo->verticeInicial;
    while(cursor != NULL){
        if(cursor->nome == nome){
            return true;
        }
        cursor = cursor->proxVertice;
    }
    return false;
}

void adicionarVertice(Grafo* grafo, char nome){
    Vertice* vertice = criarVertice(nome);

    if(verticeExiste(grafo, nome)){
        return;
    }

    if(grafo->verticeInicial == NULL){
        grafo->verticeInicial = vertice;
    } else {
        Vertice* v = grafo->verticeInicial;
        while(v->proxVertice != NULL){
            v = v->proxVertice;
        }
        v->proxVertice = vertice;
    }
    grafo->qntV += 1;
}

Vertice* retornarVertice(Vertice* verticeI, char nome){

    if(verticeI->proxVertice != NULL && verticeI->nome != nome){
        return retornarVertice(verticeI->proxVertice, nome);
    } else if(verticeI == NULL){
        printf("Vertice %c nao existe \n", nome);
    }
    return verticeI;
}

void lerArquivo(Grafo* grafo){
    int qntV, qntA, peso;
    char lixo, origem, destino, vertice;

    FILE* arquivo = fopen("dados.txt", "r");

    if(arquivo != NULL){
        fscanf(arquivo, "%d %d%c", &qntV, &qntA, &lixo);

        for(int i = 0; i < qntV; i++){
            fscanf(arquivo, "%c%c", &vertice, &lixo);
            adicionarVertice(grafo, vertice);
        }

        for(int k = 0; k < qntA; k++){
            fscanf(arquivo, "%c%c %d%c", &origem, &destino, &peso, &lixo);
            adicionarAresta(grafo, origem, destino, peso);
        }
        fclose(arquivo);
    } else {
        printf("Não foi possível abrir este arquivo\n");
    }
}

void imprimirGrafo(Grafo* grafo){
    if(grafo->verticeInicial == NULL){
        printf("Grafo nulo \n");
        return;
    }
    Vertice* v = grafo->verticeInicial;
    //printf("Vertices: %d, Arestas: %d \n", grafo->qntV, grafo->qntA);

    for(v = v; v != NULL; v = v->proxVertice){
        printf("%c -> ", v->nome);
        Aresta* a = grafo->arestaInicial;
        for(a = a; a != NULL; a = a->proxAresta){
            if(a->verticeOrigem->nome == v->nome){
                printf("%c   ", a->verticeDestino->nome);
            } else if(a->verticeDestino->nome == v->nome){
                printf("%c   ", a->verticeOrigem->nome);
            }
        }
        printf("\n");
    }

    /*for(a = a; a != NULL; a = a->proxAresta){
        printf("%c%c %d \n", a->verticeOrigem->nome, a->verticeDestino->nome, a->peso);
    }*/
}

vector<char> substituir_no_Vetor(vector<char> vetor, char x, char y){
    for(int i = 0; i < vetor.size(); i++){
        if(vetor[i] == x){
            vetor[i] = y;
        }
    }
    return vetor;
}

Grafo* kruskal(Grafo* grafo){
    Grafo* resultado = iniciarGrafo(1);
    Aresta* cursor = grafo->arestaInicial;
    vector<char> vetor;

    vector<char> dicionario = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    for(int i = 0; i < grafo->qntV; i++){
        vetor.push_back(dicionario[i]);
    }
    vector<char> vetorBKP = vetor;

    unordered_set<char> conjVertices;

    while(cursor != NULL){
        char x, y;

        x = cursor->verticeOrigem->nome;
        y = cursor->verticeDestino->nome;

        char auxX, auxY;

        bool a = conjVertices.find(x) != conjVertices.end();
        bool b = conjVertices.find(y) != conjVertices.end();
        if(a == 0 || b == 0) {
            conjVertices.insert(x);
            conjVertices.insert(y);
            vetor = substituir_no_Vetor(vetor, x, y);

            adicionarVertice(resultado, x);
            adicionarVertice(resultado, y);
            adicionarAresta(resultado, x, y, cursor->peso);

        } else {
            int valorVetorX = -1;
            int valorVetorY = -1;
            for(int i = 0; i < grafo->qntA; i++) {
                if(vetorBKP[i] == x) {
                    valorVetorX = i;
                } else if(vetorBKP[i] == y) {
                    valorVetorY = i;
                }
            }

            if(vetor[valorVetorX] != vetor[valorVetorY]){
                conjVertices.insert(x);
                conjVertices.insert(y);
                vetor = substituir_no_Vetor(vetor, vetor[valorVetorX], vetor[valorVetorY]);

                adicionarVertice(resultado, x);
                adicionarVertice(resultado, y);
                adicionarAresta(resultado, x, y, cursor->peso);
            }
        }
        cursor = cursor->proxAresta;
    }




    /*unordered_set<char>::iterator aux;
    for(aux = conjVertices.begin(); aux != conjVertices.end(); aux++){
        cout << *aux << endl;
    }*/
    return resultado;
}

int main(void){
    Grafo* grafo = iniciarGrafo(1);
    lerArquivo(grafo);
    printf("Grafo antes de Kruskal \n\n");
    imprimirGrafo(grafo);
    printf("-------------------------------------\n");
    printf("Grafo pós Kruskal\n\n");
    Grafo* resultado = kruskal(grafo);
    imprimirGrafo(resultado);

}
