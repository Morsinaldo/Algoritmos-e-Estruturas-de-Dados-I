#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct arrayqueue {
    int frente;
    int tras;
    int* elementos;
    int tamanho;    //tam do array
    int qtdade;     //qtdade de elementos no array    
};

struct arrayqueue* inicializar(int tamArray) {
    struct arrayqueue* fila = (struct arrayqueue*)malloc(sizeof(struct arrayqueue));
    fila -> elementos = (int*)calloc(tamArray, sizeof(int));
    
    fila -> tamanho = tamArray;
    fila -> frente = -1;
    fila -> tras = -1;
    fila -> qtdade = 0;
    return fila;
}

//se a fila estiver nula, instancie a fila com tamanho 10
//por causa da possibilidade de instanciacao usamos struct arrayqueue**
//se a fila encher, simplesmente não enfileire
void enfileirar(struct arrayqueue** fila, int val) {
    if((*fila) == NULL){
        (*fila) = inicializar(10);
        
    }
    
    if((*fila) -> qtdade == 0){
        (*fila) -> frente++;
        (*fila) -> elementos[(*fila) -> qtdade] = val;
        (*fila) -> qtdade++;
        (*fila) -> tras++;
    } else {
        if((*fila) -> qtdade != (*fila -> tamanho){
            (*fila) -> tras++;
            (*fila) -> tras = (*fila) -> tras % (*filla) -> tamanho;
            (*fila) -> elementos[(*fila)->tras] = val;
            (*fila) -> qtdade++;
        } else {
            return;
        }
    }

    
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int desenfileirar(struct arrayqueue* fila) {
    if(fila -> qtdade == 0 || (fila == NULL)){
        return INT_MIN;
    } else {
        fila -> frente++;
        fila -> qtdade--;
    }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct arrayqueue* fila) {
    if(fila -> qtdade == 0 || (fila == NULL)){
        return INT_MIN;
    } else {
        return fila -> frente;
    }
}