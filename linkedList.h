#include <stdlib.h>
#include <stdio.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar() {
    struct linkedlist* lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));

    lista -> cabeca = NULL;
    lista -> qtdade = 0;

    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo -> val = valor;
    novoNo -> prox = NULL;

    return novoNo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {
    struct no* novoNo = alocarNovoNo(valor);
    
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        
        do {
            aux = aux->prox;
            if (aux == NULL) { // Chegamos no fim da lista
                aux -> prox = novoNo;
            }
        } while (aux != NULL);
        
    }
    else {
        lista -> cabeca = novoNo;
    }

    lista -> qtdade++;
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor) {
    struct no* novoNo = alocarNovoNo(valor);
    if(lista -> cabeca == NULL){
        lista -> cabeca = novoNo;
    } else {
        struct no* aux = lista -> cabeca;
        lista -> cabeca = novoNo -> prox;
        novoNo -> prox = aux -> prox;
    }
    lista -> qtdade++;
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao) {
    if(posicaoEhValida(lista,posicao)){
        struct no* novoNo = alocarNovoNo(valor);
        struct no* aux = lista -> cabeca

        for(int i = 0; i < posicao; i++){
            aux = aux -> prox;
        }

        novoNo -> prox = aux -> prox;
        aux -> prox = novoNo;

        lista -> qtdade++;
    }
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    if(posicaoEhValida(lista, posicao)){
        if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        
            while(aux != NULL){
                aux = aux -> prox;
                if(aux == NULL){
                    return aux -> val;
                }
            }               
        }
    }
}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao) {
    if(posicaoEhValida(lista,posicao)){
        struct no* aux = lista -> cabeca;
        struct no* aux2;

        for(int i = 0; i < posicao; i++){
            aux = aux -> prox;
            if(i == posicao - 2){
                aux2 = aux;
            }
        }
        aux2 = aux;
        free(aux);
        lista -> qtdade--;
    }
}

void imprimirLista(struct linkedlist* lista) {
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista está vazia!");
    }
}

bool posicaoEhValida(struct linkedlist* lista, int posicao){
    if(posicao >=0 && posicao < lista -> qtdade){
        return true;
    } else {
        return false;
    }
}