#include <stdio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

void insertionSortIP(int* v, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int valor = v[i];
        int j;
        for (j = i; j > 0 && v[j - 1] > valor; j--) {
            v[j] = v[j - 1];
        }
        v[j] = valor;
    }
}

int* insertionSortOP(int* v, int tamanho){
  int* ordenado = (int*)malloc(tamanho*sizeof(int));
  ordenado[0] = v[0];
  for(int i = 1; i < tamanho; i++){
    int j;
    for(j = 0; j < i; j++){
      if(ordenado[j] > v[i]){
        for(int k = i; k > 0 ; k--){
          ordenado[k] = ordenado[k-1];
        }
        break;
      }
    }
    ordenado[j] = v[i];
  }
  return ordenado;
}


int main() {
  int tamanho = 5;
  int* v = (int*)calloc(tamanho, sizeof(int));

  v[0] = 5;
  v[1] = 3;
  v[2] = 6;
  v[3] = 1;
  v[4] = 2;

  insertionSortIP(v,tamanho);
  for(int i = 0; i < tamanho; i++){
    printf("%d ", v[i]);
  }

  free(v);
  return 0;
}