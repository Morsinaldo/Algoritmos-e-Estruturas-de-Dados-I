#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
- um algoritmo de divisão e conquista
- estável
- recursivo 
- out-of-place: O(n), se apagarmos os vetores que não são mais usados (sendo mais específico, θ(n))
- complexidade de tempo: O(nlogn).
    - a altura da recursão até chegar no caso base log(n)
    - em cada nível executamos o merge em estruturas menores, que somados custam O(n)
*/

void merge(int* v, int* v1, int tV1, int* v2, int tV2){
  int i = 0; // indice do vetor v
  int j = 0; // indice do vetor v1
  int k = 0; // indice do vetor v2

  while(j < tV1 && k < tV2){
    if(v1[j] < v2[k]){
      v[i] = v1[j];
      j++;
    } else {
      v[i] = v2[k];
      k++;
    }
    i++;
  }

  // Caso ainda sobre elementos que não foram preenchidos, deve-se colocálos no vetor V

  // Caso sobrem elementos na esquerda
  while(j < tV1){
    v[i] = v1[j];
    j++;
    i++;
  }

  // caso sobrem elementos na direita
  while(k < tV2){
    v[i] = v2[k];
    k++;
    i++;
  }
}

void mergeSort(int* v, int tam){
  if(tam > 1){
    // tamanho dos vetores
    int meio = tam/2;
    int tV1 = meio;
    int tV2 = tam - meio;

    // Particionando o vetor
    int* v1 = (int*)malloc(tV1*sizeof(int));
    for(int i = 0; i< meio; i++){
      v1[i] = v[i];
    }

    int* v2 = (int*)malloc(tV2*sizeof(int));
    for(int i = meio; i < tam; i++){
      v2[i-meio] = v[i];
    }

    // Chama recursivamente o mergeSort
    mergeSort(v1,tV1);
    mergeSort(v2,tV2);
    merge(v,v1,tV1,v2,tV2);

    // Libera a memória alocada
    free(v1);
    free(v2);
  }
}

void preencherVetorCrescente(int* v, int tam){
  for(int i = 0; i < tam; i++){
    v[i] = i;
  }
}

void preencherVetorDecrescente(int* v, int tam){
  int j = 0;
  for(int i = tam-1; i > 0; i--){
    v[j] = i;
    j++;
  }
}

void preencherVetorAleatorio(int*v, int tam, int nMax){
  for(int i = 0; i < tam; i++){
    v[i] = rand()%nMax;
  }
}

int main(void) {

  clock_t Ticks[2];
  // -------- VETOR PEQUENO --------
  int tamanhoVPequeno = 10;
  int* v = (int*)calloc(tamanhoVPequeno, sizeof(int));

  // -------- VETOR GRANDE --------
  int tamanhoVGrande = 1000000;
  int* vg = (int*)calloc(tamanhoVGrande, sizeof(int));

  // -------- VETOR CRESCENTE --------

  preencherVetorCrescente(v,tamanhoVPequeno);
  Ticks[0] = clock();
  mergeSort(v,tamanhoVPequeno);
  Ticks[1] = clock();
  double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições crescente: %g ms.\n", Tempo);

  preencherVetorCrescente(vg,tamanhoVGrande);
  Ticks[0] = clock();
  mergeSort(vg,tamanhoVGrande);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições crescente: %g ms.\n", Tempo);
  

  // -------- VETOR DECRESCENTE --------  
  preencherVetorDecrescente(v,tamanhoVPequeno);
  Ticks[0] = clock();
  mergeSort(v,tamanhoVPequeno);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições decrescente: %g ms.\n", Tempo);

  preencherVetorDecrescente(vg,tamanhoVGrande);
  Ticks[0] = clock();
  mergeSort(vg,tamanhoVGrande);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições decrescente: %g ms.\n", Tempo);

  // -------- VETOR ALEATÓRIO ---------
  preencherVetorAleatorio(v,tamanhoVPequeno, 100);
  Ticks[0] = clock();
  mergeSort(v,tamanhoVPequeno);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições aleatório: %g ms.\n", Tempo);

  preencherVetorAleatorio(vg,tamanhoVGrande, 1000000);
  Ticks[0] = clock();
  mergeSort(vg,tamanhoVGrande);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições aleatório: %g ms.\n", Tempo);
  
  free(v);
  free(vg);

  
  return 0;
}