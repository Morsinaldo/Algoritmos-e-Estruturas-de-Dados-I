#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

int* selectionSortOP(int* v, int tamanho){
  
    int* ordenado = (int*)calloc(tamanho, sizeof(int));

    int indexMenor = 0;
    for(int cont = 0; cont < tamanho; cont++){
        for(int i = 0; i < tamanho; i++){
            if(v[i] < v[indexMenor])
                indexMenor = i;
        }
        ordenado[cont] = v[indexMenor];
        v[indexMenor] = INT_MAX;
    }
    return ordenado;
}


int* selectionSortIP(int* v, int tamanho){
  for(int i = 0; i < tamanho-1; i++){
    int indexMenor = i;
    for(int j = i; j < tamanho; j++){
      if(v[j] < v[indexMenor]){
        indexMenor = j;
      }
    }
    int aux = v[i];
    v[i] = v[indexMenor];
    v[indexMenor] = aux;
  }
  return v;
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

int main() {
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
  selectionSortIP(v,tamanhoVPequeno);
  Ticks[1] = clock();
  double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições crescente: %g ms.\n", Tempo);

  preencherVetorCrescente(vg,tamanhoVGrande);
  Ticks[0] = clock();
  selectionSortIP(vg,tamanhoVGrande);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições crescente: %g ms.\n", Tempo);
  

  // -------- VETOR DECRESCENTE --------  
  preencherVetorDecrescente(v,tamanhoVPequeno);
  Ticks[0] = clock();
  selectionSortIP(v,tamanhoVPequeno);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições decrescente: %g ms.\n", Tempo);

  preencherVetorDecrescente(vg,tamanhoVGrande);
  Ticks[0] = clock();
  selectionSortIP(vg,tamanhoVGrande);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições decrescente: %g ms.\n", Tempo);

  // -------- VETOR ALEATÓRIO ---------
  preencherVetorAleatorio(v,tamanhoVPequeno, 100);
  Ticks[0] = clock();
  selectionSortIP(v,tamanhoVPequeno);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições aleatório: %g ms.\n", Tempo);

  preencherVetorAleatorio(vg,tamanhoVGrande, 1000000);
  Ticks[0] = clock();
  selectionSortIP(vg,tamanhoVGrande);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições aleatório: %g ms.\n", Tempo);
  
  free(v);
  free(vg);
  return 0;
  
}