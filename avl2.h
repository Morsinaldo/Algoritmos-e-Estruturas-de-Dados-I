#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct avl {
    struct noBstAvl* raiz;
    int tam;
};

struct noBstAvl {
    int val;
    int altura;
    int balanco;
    struct noBstAvl* esq;
    struct noBstAvl* dir;
};

// Assinaturas
void inserir(struct avl* avl, int val);
struct noBstAvl* rotacaoEsquerda(struct noBstAvl* arvore);
struct noBstAvl* rotacaoDireita(struct noBstAvl* arvore);
void atualizar(struct noBstAvl* no);
struct noBstAvl* balancear(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no);

/**
 * Funcao que aloca uma nova arvore avl.
 **/
struct avl* alocarAvl() {
    struct avl* tree = (struct avl*)malloc(sizeof(struct avl));
    tree->raiz = NULL;
    tree->tam = 0;
    return tree;
}

/**
 * Funcao que aloca um novo noBstAvl, e
 * ajusta os ponteiros esq e dir para NULL,
 * e variáveis altura e balanco para 0.
 **/
struct noBstAvl* alocarNovoNo(int val) {
    struct noBstAvl* novoNo = (struct noBstAvl*)malloc(sizeof(struct noBstAvl));
    novoNo->val = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura=0;
    novoNo->balanco=0;
    return novoNo;
}

/**
 * Funcao que rotaciona uma arvore para a
 * direita e retorna a nova raiz.
 **/
struct noBstAvl* rotacaoDireita(struct noBstAvl* arvore) {
    struct noBstAvl* novaRaiz = arvore->esq;
    arvore->esq = novaRaiz->dir;
    novaRaiz->dir = arvore;
    atualizar(arvore);
    atualizar(novaRaiz);
    return novaRaiz;
}

/**
 * Funcao que rotaciona uma arvore para a
 * esquerda e retorna a nova raiz.
 **/
struct noBstAvl* rotacaoEsquerda(struct noBstAvl* arvore) {
    struct noBstAvl* novaRaiz = arvore->dir;
    arvore->dir = novaRaiz->esq;
    novaRaiz->esq = arvore;
    atualizar(arvore);
    atualizar(novaRaiz);
    return novaRaiz;
}

/**
 * Funcao que recebe a raiz de uma bstAvl, e
 * insere um novo valor nela. 
 * Raiz é passada por referência (ponteiro de ponteiro).
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó inserido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de inserir de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/
void inserirNo(struct noBstAvl* raiz, struct noBstAvl* novoNo) {
    if (novoNo->val <= raiz->val && raiz->esq != NULL) {
        inserirNo(raiz->esq, novoNo);
    }
    else if (novoNo->val <= raiz->val && raiz->esq == NULL) {
        raiz->esq = novoNo;
    }
    else if (novoNo->val > raiz->val && raiz->dir != NULL) {
        inserirNo(raiz->dir, novoNo);
    }
    else if (novoNo->val > raiz->val && raiz->dir == NULL) {
        raiz->dir = novoNo;
    }
  atualizar(raiz);
  balancear(raiz);
}

/**
 * Funcao fachada para insercao, similar a funcao de
 * insercao na BST.
 * Lembrar de incrementar tamanho.
 **/
void inserir(struct avl* avl, int val) {
    struct noBstAvl* novoNo = alocarNovoNo(val);
    if (avl->tam == 0) {
        avl->raiz = novoNo;
    }
    else {
        inserirNo(avl->raiz, novoNo);
    }
    avl->tam++;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e atualiza sua altura
 * e fator de balanço.
 * Lembre que a altura das sub-árvores direita e esquerda
 * não vão mudar, por isso a implementação não é tão complicada.
 **/
void atualizar(struct noBstAvl* no) {
    int hEsq = 0;
    int hDir = 0;
  
    if(no->esq!=NULL)
      hEsq = no->esq->altura;
    else
      hEsq = -1;
  
    if(no->dir!=NULL)
      hDir = no->dir->altura;
    else
      hEsq = -1;
    
    if(hEsq > hDir)
        no->altura = hEsq + 1;
    else
        no->altura = hDir + 1;
  
    if(no->altura == 0)
      no->balanco = 0;
    else
      no->balanco = hDir - hEsq;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e identifica em qual caso
 * ela se encaixa para executar os procedimentos de balanceamento
 * corretos:
 *      - Caso 1: esquerda-esquerda e esquerda-cheio
 *      - Caso 2: esquerda-direita
 *      - Caso 3: direita-direita e direita-cheio
 *      - Caso 4: direita-esquerda
 * Lembrar que quando há balanceamento temos uma nova raiz
 * que deve ser retornada para a função que chama o balanceamento.
 * Dica: usar fator de balanço do nó e de uma de suas sub-árvores
 * para descobrir qual é o caso.
 **/
struct noBstAvl* balancear(struct noBstAvl* no) {
    if(no-> balanco == -2){
        if(no->esq->balanco <= 0){
            no = rebalancearEsqEsq(no);
          return no;
        } else {
            no = rebalancearEsqDir(no);
        }
    } else if(no -> balanco == 2){
        if(no->dir->balanco <= 0){
            no = rebalancearDirEsq(no);
            return no;
        } else {
            no = rebalancearDirDir(no);
            return no;
        }
    } else {
        return no;
    }
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 1.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no) {
    return rotacaoDireita(no);
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 2.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no) {
    no -> esq = rotacaoEsquerda(no->esq);
    return rotacaoDireita(no);
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 3.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no) {
    return rotacaoEsquerda(no);
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 4.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no) {
    no->dir = rotacaoDireita(no->dir);
    return rotacaoEsquerda(no);
}

/**
 * Funcao que retorna o maior valor de uma árvore AVL.
 * Mesma implementação da BST.
 **/
int max(struct noBstAvl* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->dir != NULL) {
        return max(raiz->dir);
    }
    else {
        return raiz->val;
    }
}

/**
 * Funcao que retorna o menor valor de uma árvore AVL.
 * Mesma implementação da BST.
 **/
int min(struct noBstAvl* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->esq != NULL) {
        return min(raiz->esq);
    }
    else {
        return raiz->val;
    }
}

/**
 * Funcao que recebe a raiz de uma árvore AVL, e
 * remove o nó que contem o valor passado como
 * argumento. 
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó removido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de remover de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/
struct noBstAvl* removerNo(struct noBstAvl* raiz, int val) {
    if (raiz == NULL)
        return raiz;
    else {
        if (val < raiz->val) {
            raiz->esq = removerNo(raiz->esq, val);
            //atualizar(raiz);
        }
        else if (val > raiz->val) {
            raiz->dir = removerNo(raiz->dir, val);
            //atualizar(raiz);
        }
        else {
            if (raiz->esq == NULL && raiz->dir == NULL) { // Caso1 : Nó folha
                free(raiz);
                return NULL;
            }
            else if (raiz->esq != NULL && raiz->dir == NULL) { // Caso 2 : Tem um filho na esquerda
                struct noBstAvl* aux = raiz->esq;
                free(raiz);
                return aux;
            }
            else if (raiz->esq == NULL && raiz->dir != NULL) { // Caso 2 : Tem um filho na direita
                struct noBstAvl* aux = raiz->dir;
                free(raiz);
                return aux;
            }
            else { // Caso 3
                int minimo = min(raiz->dir);
                raiz->val = minimo;
                removerNo(raiz->dir, raiz->val);
            }
        }
        atualizar(raiz);
        raiz = balancear(raiz);
        return raiz;
    }
}

/**
 * Funcao fachada para remocao, similar a funcao de
 * remocao na BST.
 * Lembrar de decrementar tamanho.
 **/
void remover(struct avl* avl, int val) {
    /*if (removerNo(avl->raiz, val) != NULL) {
        avl->tam--;
    }*/
  
  if (avl->raiz != NULL) {
    struct noBstAvl* no = removerNo(avl->raiz, val);
    if (no != NULL)
      avl->raiz = no;
    avl->tam--;
  }
}