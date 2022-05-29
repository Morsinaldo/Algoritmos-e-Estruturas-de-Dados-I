#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void bubbleSort(int* v, int n){
  bool troca = false;
  for(int i = 0; i < n-1; i++){
    troca = false;
    for(int j = 0; j < n-i-1; j++){
      if(v[j+1]<v[j]){
        int aux = v[j];
        v[j] = v[j+1];
        v[j+1] = aux;
        troca = true;
      }
    }
    if(troca == false){
        break;
      }
  }
}

int main() {
  //2, 8, 6, 10, 4, 5, 3
  int tamanho = 7;
  int* v = (int*)calloc(tamanho, sizeof(int));
  v[0] = 2;
  v[1] = 8;
  v[2] = 6;
  v[3] = 10;
  v[4] = 4;
  v[5] = 5;
  v[6] = 3;

  bubbleSort(v,tamanho);
  for(int i = 0; i < tamanho; i++){
    printf("%d ", v[i]);
  }
  
}