#include <stdlib.h>
#include <stdio.h>
#include "listaAdjacente.h"

int main(void){
    Lista* lista = initList();
    lista = lerArquivo(lista);
    imprimirListaC(lista);

    return 0;
}
