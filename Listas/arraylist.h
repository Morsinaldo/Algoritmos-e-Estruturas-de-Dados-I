#include <stdio.h>
#include <stdlib.h>

struct arraylist
{
    int* vetor;
    int qtdade; // quantidade de valores armazenados
    int capacidade; // tamanho total do vetor
};

struct arraylist* inicializar(int capacidade)
{
    // 1- alocando a memoria para o struct
    struct arraylist* lista = (struct arraylist*)malloc(sizeof(struct arraylist));

    // 2 - alocando a memoria para o vetor (calloc inicializa tudo com 0)
    lista->vetor = (int*)calloc(capacidade, sizeof(int));

    // 3 - alocando os valores qtd e tam do struct
    lista->qtdade = 0;
    lista->capacidade = capacidade;

    return lista;
};

void duplicarCapacidade(struct arraylist* lista) {
    lista->vetor = (int*)realloc(lista->vetor, 2 * lista->capacidade * sizeof(int));
    lista->capacidade = lista->capacidade * 2;
}

void inserirElementoNoFim(struct arraylist* lista, int valor) {
    if (lista->qtdade == lista->capacidade) {
        duplicarCapacidade(lista);
    }

    lista->vetor[lista->qtdade] = valor;
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct arraylist* lista, int valor, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) { // posicao informada eh valida
        if (lista->qtdade == lista->capacidade) { // a lista esta toda preenchida
            duplicarCapacidade(lista);
        }

        for (int i = lista->qtdade; i > posicao; i--) {
            lista->vetor[i] = lista->vetor[i - 1];
        }
        lista->vetor[posicao] = valor;
        lista->qtdade++;
    }
}

void removerElementoNoFim(struct arraylist* lista) {
    lista->qtdade--;
}

void removerElementoEmPosicao(struct arraylist* lista, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) { // posicao informada eh valida
        for (int i = posicao; i < lista->qtdade - 1; i++) {
            lista->vetor[i] = lista->vetor[i + 1];
        }
        lista->qtdade--;
    }
}

void atualizarElemento(struct arraylist* lista, int valor, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) { // posicao informada eh valida
        lista->vetor[posicao] = valor;
    }
}

int obterElementoEmPosicao(struct arraylist* lista, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) { // posicao informada eh valida
        return lista->vetor[posicao];
    }
    else {
        return 0;
    }
}


void exibirLista(struct arraylist* lista) {
    printf("[");
    for (int i = 0; i < lista->qtdade; i++) {
        printf("%d", lista->vetor[i]);
        if (i < lista->qtdade - 1) {
            printf(", ");
        }
    }
    printf("]");
}