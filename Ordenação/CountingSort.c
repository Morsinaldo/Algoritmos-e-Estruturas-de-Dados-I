#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int* countingSort(int* v, int tam){

  // v = [9,5,8,2,4]
   
  // 1 passo descobrir o maior e o menor valor
  int menor = v[0];
  int maior = v[0];
  for(int i = 0; i < tam; i++){
    if(v[i] > maior){
      maior = v[i];
    }
    if(v[i] < menor){
      menor = v[i];
    }
  }

  // v = [9,5,8,2,4]
  // maior = 9, menor = 2

  // 2° passo - construir um vetor de ocorrencias
  int tamOcorrencias = maior - menor + 1; // 9 - 2 + 1 = 8
  int *vOcorrencias = (int*)calloc(tamOcorrencias,sizeof(int));

  // [2,3,4,5,6,7,8,9]
  // [0,0,0,0,0,0,0,0]

  // i = 0
  // vOcorrencias[7] = v[0]
  // vOcorrencias[3] = v[1]
  // vOco
  for(int i = 0; i < tam; i++){
    int valor = v[i];
    vOcorrencias[valor - menor]++;
  }
    
  // [1,0,1,1,0,0,1,1]

  // 3° passo - fazer a soma comulativa
  for(int i = 1; i < tamOcorrencias; i++){
    vOcorrencias[i] += vOcorrencias[i-1];
  }

  // 4° passo - descobrir a posição final de cada elemento
  int* newV = (int*)malloc(tam*sizeof(int));

  for(int i = 0; i < tam; i++){
    int valor = v[i];
    int indexVOcorrencias = vOcorrencias[valor - menor];
    newV[indexVOcorrencias - 1] = valor;
    vOcorrencias[valor - menor]--;
  }
  
  return newV;

  // bom desempenho com quando a diferença do maior valor e do menor valor é pequena
  // O(n + (maior-menor))
  
}

int* preencherVetorCrescente(int* v, int tam){
  for(int i = 0; i < tam; i++){
    v[i] = i;
  }
  return v;
}

int* preencherVetorDecrescente(int* v, int tam){
  int j = 0;
  for(int i = tam-1; i > 0; i--){
    v[j] = i;
    j++;
  }
  return v;
}

int* preencherVetorAleatorio(int*v, int tam, int nMax){
  for(int i = 0; i < tam; i++){
    v[i] = rand()%nMax;
  }
  return v;
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

  v = preencherVetorCrescente(v,tamanhoVPequeno);
  Ticks[0] = clock();
  v = countingSort(v,tamanhoVPequeno);
  Ticks[1] = clock();
  double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições crescente: %g ms.\n", Tempo);

  for(int i = 0; i < tamanhoVPequeno; i++){
    printf("%d ", v[i]);
  }
  printf("\n");

  vg = preencherVetorCrescente(vg,tamanhoVGrande);
  Ticks[0] = clock();
  vg = countingSort(vg,tamanhoVGrande);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições crescente: %g ms.\n", Tempo);

  // -------- VETOR DECRESCENTE --------  
  v = preencherVetorDecrescente(v,tamanhoVPequeno);
  Ticks[0] = clock();
  v = countingSort(v,tamanhoVPequeno);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições decrescente: %g ms.\n", Tempo);

  for(int i = 0; i < tamanhoVPequeno; i++){
    printf("%d ", v[i]);
  }
  printf("\n");

  vg = preencherVetorDecrescente(vg,tamanhoVGrande);
  Ticks[0] = clock();
  vg = countingSort(vg,tamanhoVGrande);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições decrescente: %g ms.\n", Tempo);

  for(int i = 0; i < tamanhoVPequeno; i++){
    printf("%d ", v[i]);
  }
  printf("\n");

  // -------- VETOR ALEATÓRIO ---------
  v = preencherVetorAleatorio(v,tamanhoVPequeno, 10);
  Ticks[0] = clock();
  v = countingSort(v,tamanhoVPequeno);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições aleatório: %g ms.\n", Tempo);

  for(int i = 0; i < tamanhoVPequeno; i++){
    printf("%d ", v[i]);
  }
  printf("\n");

  // -------- VETOR ALEATÓRIO ---------
  v = preencherVetorAleatorio(v,tamanhoVPequeno, 100000000);
  Ticks[0] = clock();
  v = countingSort(v,tamanhoVPequeno);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 10 posições aleatório de 0 a 100 milhões: %g ms.\n", Tempo);

  vg = preencherVetorAleatorio(vg,tamanhoVGrande, 1000000);
  Ticks[0] = clock();
  vg = countingSort(vg,tamanhoVGrande);
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto com o vetor de 1 milhão de posições aleatório: %g ms.\n", Tempo);
  
  free(v);
  free(vg);
  
  return 0;
}