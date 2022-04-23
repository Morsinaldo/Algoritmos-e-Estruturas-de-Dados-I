#include <stdlib.h>
#include <stdio.h>

struct no{
    struct no *ant;
    int val;
    struct no *prox;
};

struct doublylinkedlist {
    struct no* cabeca;
    struct no* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializar() {
    struct doublylinkedlist* lista = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));

    lista -> cabeca = NULL;
    lista -> cauda = NULL;
    lista -> qtdade = 0;

    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo -> val = valor;
    novoNo -> prox = NULL;
    novoNo -> ant = NULL;

    return novoNo;
}

void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor){
    struct no* novoNo = alocarNovoNo(valor);
    if(lista -> cabeca == NULL){
        lista -> cabeca = novoNo;
    } else {

        novoNo -> prox = lista -> cabeca;
        lista -> cabeca = novoNo;
        //novoNo -> anterior = lista -> cabeca; // novoNo -> anterior deve ser nulo, pela estrutura da Doubly Linked List

        // Como fazer o próximo apontar para o Novo nó? (Resolvido?)
        struct no* aux = lista->cabeca;

        //navega partindo da cabeça até chegar NULL
        while(aux->prox != NULL){
            aux = aux->prox;
        }

        aux -> ant = novoNo;
    }
    lista -> qtdade++;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor) {
    struct no* novoNo = alocarNovoNo(valor);
    
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        
        while(aux->prox != NULL){
            aux = aux->prox;
        }

        aux->prox = novoNo;
        
    }
    else {
        lista -> cabeca = novoNo;
    }

    lista -> qtdade++;
}

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao) {
    if(posicao >= 0 && posicao <= lista->qtdade){

        if(posicao == 0){
            inserirElementoNoInicio(lista,valor);
        } else if (posicao == lista -> qtdade){
            inserirElementoNoFim(lista,valor);
        } else {
            struct no* novoNo = alocarNovoNo(valor);
            struct no* aux = lista -> cabeca;
            int i = 0;

            for(i; i < posicao-1; i++){ // posicao -1?
                aux = aux -> prox;
            }

            novoNo -> prox = aux -> prox;
            aux -> prox = novoNo;
            novoNo -> ant = aux;

            for(i; i <= posicao; i++){
                aux = aux -> prox;
            }

            aux -> ant = novoNo;

            lista -> qtdade++;
        }
    }
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    if(posicao >= 0 && posicao < lista->qtdade){  
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        
            for(int i = 0; i < posicao; i++){
                aux = aux -> prox;
            }
            return aux -> val;              
    }
}

void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao){
    if(posicao >= 0 && posicao < lista->qtdade){
        struct no* aux = lista -> cabeca;
        if(posicao == 0){
            lista -> cabeca = aux -> prox;
            free(aux);
            lista -> qtdade--;
        } else {
            for(int i = 0; i < posicao - 1; i++){
                aux = aux -> prox;
            }

            struct no* aux2 = aux -> prox;
            struct no* aux3 = aux;
            aux -> prox = aux2 -> prox;
            free(aux2);
            aux = aux -> prox;
            aux -> ant = aux3;
            
            lista -> qtdade--;
        }
    }
}

void imprimirLista(struct no** cabeca) {
    //usamos o aux para percorrer a lista
    if ((*cabeca) != NULL) {
        struct no* aux = (*cabeca);
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

/* For testing purposes
int main(void) {
struct doublylinkedlist* lista = inicializar();
struct no** cabecaNo = (struct no**)malloc(sizeof(struct no));
  cabecaNo = lista;

  
  inserirElementoNoInicio(lista,3);
  int elemento = obterElementoEmPosicao(lista,0);
  printf("%d \n", elemento);

  inserirElementoNoInicio(lista,4);
  elemento = obterElementoEmPosicao(lista,0);
  int elemento2 = obterElementoEmPosicao(lista,1);
  printf("%d \n", elemento);
  printf("%d \n", elemento2);
  
  inserirElementoNoFim(lista,5);
  int elemento = obterElementoEmPosicao(lista,0);
  printf("%d \n", elemento);

  inserirElementoNoFim(lista,6);
  elemento = obterElementoEmPosicao(lista,0);
  int elemento2 = obterElementoEmPosicao(lista,1);
  printf("%d \n", elemento);
  printf("%d \n", elemento2);
  
  inserirElementoNoInicio(lista,0);
  inserirElementoNoFim(lista,1);
  inserirElementoNoFim(lista,2);
  inserirElementoNoFim(lista,3);
  imprimirLista(cabecaNo);
  
  inserirElementoEmPosicao(lista,4,2);
  imprimirLista(cabecaNo);

  removerElementoEmPosicao(lista,3);
  imprimirLista(cabecaNo);
  
  free(lista);
  //free(cabecaNo);
  return 0;
}
*/