#include <stdio.h>
#include <stdbool.h>

struct bst {
    struct noBst* raiz;
    int tam;
};

struct noBst {
    int val;
    struct noBst* esq;
    struct noBst* dir;
};

// Assinaturas
struct noBst* alocarNoBst(int val);
struct bst* alocarBst();
void inserir(struct bst* bst, int val, bool rec);
void inserirNoIt(struct noBst* raiz, struct noBst* novoNo);
void inserirNoRec(struct noBst* raiz, struct noBst* novoNo);
bool buscar(struct bst* bst, int val, bool rec);
bool buscarRec(struct noBst* raiz, int val);
bool buscarIt(struct noBst* raiz, int val);
int min(struct noBst* raiz);
int max(struct noBst* raiz);
int altura(struct noBst* raiz);
void remover(struct bst* bst, int v);
struct noBst* removerRec(struct noBst* raiz, int val);
void navEmOrdem(struct noBst* raiz);
void navPreOrdem(struct noBst* raiz);
void navPosOrdem(struct noBst* raiz);

struct noBst* alocarNoBst(int val) {
    struct noBst* novoNo = (struct noBst*)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
};

struct bst* alocarBst() {
    struct bst* tree = (struct bst*)malloc(sizeof(struct bst));
    tree->raiz = NULL;
    tree->tam = 0;
    return tree;
};

void inserir(struct bst* bst, int val, bool rec) {
    struct noBst* novoNo = alocarNoBst(val);
    if (bst->tam == 0) {
        bst->raiz = novoNo;
    }
    else {
        if (rec)
            inserirNoRec(bst->raiz, novoNo);
        else
            inserirNoIt(bst->raiz, novoNo);
    }
    bst->tam++;
}

void inserirNoIt(struct noBst* raiz, struct noBst* novoNo) {
    while (raiz != NULL) {
        if (novoNo->val <= raiz->val && raiz->esq != NULL) {
            raiz = raiz->esq;
        }
        else if (novoNo->val <= raiz->val && raiz->esq == NULL) {
            raiz->esq = novoNo;
            return;
        }
        else if (novoNo->val > raiz->val && raiz->dir != NULL) {
            raiz = raiz->dir;
        }
        else if (novoNo->val > raiz->val && raiz->dir == NULL) {
            raiz->dir = novoNo;
            return;
        }
    }
}

void inserirNoRec(struct noBst* raiz, struct noBst* novoNo) {
    if (novoNo->val <= raiz->val && raiz->esq != NULL) {
        raiz = raiz->esq;
        inserirNoRec(raiz, novoNo);
    }
    else if (novoNo->val <= raiz->val && raiz->esq == NULL) {
        raiz->esq = novoNo;
        return;
    }
    else if (novoNo->val > raiz->val && raiz->dir != NULL) {
        raiz = raiz->dir;
        inserirNoRec(raiz, novoNo);
    }
    else if (novoNo->val > raiz->val && raiz->dir == NULL) {
        raiz->dir = novoNo;
        return;
    }
}

bool buscar(struct bst* bst, int val, bool rec) {
    bool encontrou = false;
    if (bst->raiz == NULL)
        return false;
    else if (rec)
        return buscarRec(bst->raiz, val);
    else
        return buscarIt(bst->raiz, val);
}

bool buscarRec(struct noBst* raiz, int val) {
    if (val == raiz->val) {
        return true;
    }
    else if (val < raiz->val && raiz->esq != NULL) {
        return buscarRec(raiz->esq, val);
    }
    else if (val > raiz->val && raiz->dir != NULL) {
        return buscarRec(raiz->dir, val);
    }
    else {
        return false;
    }
}

bool buscarIt(struct noBst* raiz, int val) {
    while (raiz != NULL) {
        if (raiz->val == val)
            return true;
        else if (val < raiz->val)
            raiz = raiz->esq;
        else if (val > raiz->val)
            raiz = raiz->dir;
    }
    return false;
}

int min(struct noBst* raiz) {
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

int max(struct noBst* raiz) {
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

int altura(struct noBst* raiz) {
    if (raiz == NULL) {
        return 0;
    } else {
        int hEsquerda = altura(raiz->esq);
        int hDireita = altura(raiz->dir);
        
        if (raiz->esq != NULL)
            hEsquerda = altura(raiz->esq) + 1;
        if (raiz->dir != NULL)
            hDireita = altura(raiz->dir) + 1;

        if (hEsquerda > hDireita)
            return hEsquerda;
        else
            return hDireita;
    }
}

void remover(struct bst* bst, int val) {
    struct noBst* aux = (noBst*)malloc(sizeof(noBst));
    
    if (bst->raiz != NULL) {
        struct noBst* no = removerRec(bst->raiz, val);
        if (no != NULL)
            bst->raiz = no;
        bst->tam--;
    }
}

struct noBst* removerRec(struct noBst* raiz, int val){
    if (raiz == NULL)
        return raiz;
    else {
        if (val < raiz->val) {
            raiz->esq = removerRec(raiz->esq, val);
        }
        else if (val > raiz->val) {
            raiz->dir = removerRec(raiz->dir, val);
        }
        else {
            if (raiz->esq == NULL && raiz->dir == NULL) { // Caso1 : Nó folha
                free(raiz);
                return NULL;
            }
            else if (raiz->esq != NULL && raiz->dir == NULL) { // Caso 2 : Tem um filho na esquerda
                struct noBst* aux = raiz->esq;
                free(raiz);
                return aux;
            }
            else if (raiz->esq == NULL && raiz->dir != NULL) { // Caso 2 : Tem um filho na direita
                struct noBst* aux = raiz->dir;
                free(raiz);
                return aux;
            }
            else {
                int minimo = min(raiz->dir);
                raiz->val = minimo;
                removerRec(raiz->dir, raiz->val);
            }
        }
        return raiz;
    }
}


void navEmOrdem(struct noBst* raiz) {
    if (raiz == NULL)
        return;
    else {
        navEmOrdem(raiz->esq);
        printf("%d ", raiz->val);
        navEmOrdem(raiz->dir);
    }
}

void navPreOrdem(struct noBst* raiz) {
    if (raiz == NULL)
        return;
    else {
        printf("%d ", raiz->val);
        navEmOrdem(raiz->esq);
        navEmOrdem(raiz->dir);
    }
}

void navPosOrdem(struct noBst* raiz) {
    if (raiz == NULL)
        return;
    else {
        navPosOrdem(raiz->esq);
        navPosOrdem(raiz->dir);
        printf("%d ", raiz->val);
    }
}