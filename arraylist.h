#include <stdio.h>
#include <stdlib.h>

struct arraylist
{
    int* vetor;
    int qtd; // quantidade de valores armazenados
    int tam; // tamanho total do vetor
};

struct arraylist* initialize(int tam)
{
    // 1- alocando a memoria para o struct
    struct arraylist* lista = (struct arraylist*)malloc(sizeof(struct arraylist));

    // 2 - alocando a memoria para o vetor (calloc inicializa tudo com 0)
    lista -> vetor = (int*)calloc(tam, sizeof(int));

    // 3 - alocando os valores qtd e tam do struct
    lista -> qtd = 0;
    lista -> tam = tam;

    return lista;
};

void doubleSize(struct arraylist* lista){
    lista = (struct arraylist*)realloc(lista -> vetor, 2* lista -> tam * sizeof(int));
    lista -> tam = lista -> tam*2;
}

void insertElementEnd(struct arraylist* lista, int valor){
    if(lista -> qtd == lista -> tam){
        doubleSize(lista);
    }

    lista -> vetor[lista -> qtd] = valor;
    lista -> qtd++;
}

void insertElementPosition(struct arraylist* lista, int valor, int pos){
    if(pos >= 0 && pos < getSize(lista)){ // posicao informada eh valida
        if(lista -> qtd == lista -> tam){ // a lista esta toda preenchida
            doubleSize(lista);
        } 

        for(int i = getSize(lista); i >= pos; i--){
            lista -> vetor[i] = lista -> vetor[i - 1];
        }
        lista -> vetor[pos] = valor;
        lista -> qtd++;
    }
}

void removeElementEnd(struct arraylist* lista){
    lista -> qtd--;
}

void removeElementPosition(struct arraylist* lista, int pos){
    if(pos >= 0 && pos < getSize(lista)){ // posicao informada eh valida
        for (int i = pos; i < getSize(lista) - 1; i++){
            lista -> vetor[i] = lista -> vetor[i+1];
        }
        lista -> qtd--;
    }
}

void updateElementEnd(struct arraylist* lista, int valor){
    lista -> vetor[lista -> qtd - 1] = valor;
}

void updateElementPosition(struct arraylist* lista, int valor, int pos){
    if(pos >= 0 && pos < getSize(lista)){ // posicao informada eh valida
        lista -> vetor[pos] = valor;
    }
}

int getElement(struct arraylist* lista, int pos){
    if(pos >=0 && pos < getSize(lista)){ // posicao informada eh valida
        return lista -> vetor[pos];
    } else {
        return 0;
    }
}

int getSize(struct arraylist* lista){
    return lista -> qtd;
}

void showList(struct arraylist* lista){
    for(int i = 0; i < lista -> qtd; i++){
        printf("%d ", lista -> vetor[i]);
    }
    printf("\n");
}


int main(){

    struct arraylist* lista = initialize(3);

    for(int i = 0; i < 10; i++){
        insertElementEnd(lista,i+1);
    }
    showList(lista);

    removeElementEnd(lista);    
    showList(lista);

    removeElementPosition(lista, 4); // remove o numero 5
    showList(lista);

    insertElementPosition(lista, 5, 4); // insere o numero 6
    showList(lista);

    updateElementEnd(lista, 12);
    showList(lista);

    updateElementPosition(lista, 13, 2);
    showList(lista);

    insertElementEnd(lista,14);
    insertElementEnd(lista,15);
    insertElementEnd(lista,16);
    insertElementEnd(lista,17);
    showList(lista);

    free(lista);

    return 0;
}