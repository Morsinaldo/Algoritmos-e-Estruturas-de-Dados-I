#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int*v, int x, int y){
  int aux = v[x];
  v[x] = v[y];
  v[y] = aux;
}

int particiona(int* v, int ini, int fim){
  
  int pIndex = ini;
  
  int randPivo = rand()%(fim-ini) + ini;
  int aux = v[fim];
  v[fim] = v[randPivo];
  v[randPivo] = aux;

  int pivo = v[fim];

  for(int i = ini; i < fim; i++){
    if(v[i] <= pivo){
      swap(v,i,pIndex);
      pIndex++;
    }
  }
  swap(v,pIndex,fim);
  return pIndex;
}

void quickSort(int* v, int ini, int fim){
  if(fim > ini){
    int iPivo = particiona(v,ini,fim);
    quickSort(v,ini,iPivo-1);
    quickSort(v, iPivo+1, fim);
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
  int tamanhoVGrande = 10000;
  int* vg = (int*)calloc(tamanhoVGrande, sizeof(int));

  // -------- VETOR CRESCENTE --------

  preencherVetorCrescente(v,tamanhoVPequeno);
  Ticks[0] = clock();
  quickSort(v,0,tamanhoVPequeno-1);
  Ticks[1] = clock();
  double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições crescente: %g ms.\n", Tempo);

  preencherVetorCrescente(vg,tamanhoVGrande);
  Ticks[0] = clock();
  quickSort(vg,0,tamanhoVGrande-1);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições crescente: %g ms.\n", Tempo);
  

  // -------- VETOR DECRESCENTE --------  
  preencherVetorDecrescente(v,tamanhoVPequeno);
  Ticks[0] = clock();
  quickSort(v,0,tamanhoVPequeno-1);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições decrescente: %g ms.\n", Tempo);

  preencherVetorDecrescente(vg,tamanhoVGrande);
  Ticks[0] = clock();
  quickSort(vg,0,tamanhoVGrande-1);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições decrescente: %g ms.\n", Tempo);

  // -------- VETOR ALEATÓRIO ---------
  preencherVetorAleatorio(v,tamanhoVPequeno, 100);
  Ticks[0] = clock();
  quickSort(v,0,tamanhoVPequeno-1);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições aleatório: %g ms.\n", Tempo);

  preencherVetorAleatorio(vg,tamanhoVGrande, 100);
  Ticks[0] = clock();
  quickSort(vg,0,tamanhoVGrande-1);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições aleatório: %g ms.\n", Tempo);
  
  free(v);
  free(vg);
  return 0;

}

/*
- um algoritmo de divisão e conquista
- instável
- recursivo 
- in-place: O(1)
- complexidade de tempo: 
    - O(nlogn): melhor caso e caso médio
        - a altura da recursão até chegar no caso base log(n)
        - em cada nível executamos o **particiona** em estruturas menores, que somados custam O(n)
    - O(n²): pior caso (pode ser evitado randomizando a escolha do pivô)   
*/