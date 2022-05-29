#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedqueue {
    struct no* frente;
    struct no* tras;
    int qtdade;
};

struct linkedqueue* inicializar() {
    struct linkedqueue* fila = (struct linkedqueue*)malloc(sizeof(struct linkedqueue));
    fila -> frente = NULL;
    fila -> tras = NULL;
    fila -> qtdade = 0;

    return fila;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo -> val = valor;
    novoNo -> prox = NULL;

    return novoNo;
}

bool vazia(struct linkedqueue* fila) {
    if(fila -> qtdade == 0 || (fila == NULL)){
        return true;
    } else {
        return false;
    }
}

//se a fila estiver nula, instancie a fila
//por causa da possibilidade de instanciacao usamos struct linkedqueue**
void enfileirar(struct linkedqueue** fila, int val) {
    if((*fila) == NULL){
        (*fila) = inicializar();
    }

    struct no* novoNo = alocarNovoNo(val);
    if((*fila) -> qtdade == 0){
        (*fila) -> frente = novoNo;
        (*fila) -> tras = novoNo;
        (*fila) -> qtdade++;
    } else {
        (*fila) -> tras -> prox = novoNo;
        (*fila) -> tras = novoNo;
    }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
//lembrem de desalocar o nó removido (free)
int desenfileirar(struct linkedqueue* fila) {
    if(fila -> qtdade == 0 || (fila == NULL)){
        return INT_MIN;
    } else {
        struct no* aux = fila -> frente;
        fila -> frente = aux -> prox;
        free(aux);
        fila -> qtdade--;
    }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct linkedqueue* fila) {
    if(fila -> qtdade == 0 || (fila == NULL)){
        return INT_MIN;
    } else {
        return fila -> frente -> val;
    }
}