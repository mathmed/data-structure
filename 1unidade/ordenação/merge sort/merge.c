
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>


void *merge(int *vetor, int comeco, int meio, int fim);
void *mergeSort(int* vetor, int comeco, int fim);
int *newv (unsigned int n);
double tvtosec(struct timeval t);


int main(void) 
 {

	srand(time(NULL)); 
	struct timeval a;
	struct timeval b;
	double tempo;

 	for(int n = 1000; n <= 10000; n += 100){

 		tempo = 0;

 		for(int i = 0; i < 3000 ; i++){
 
		 	int *v = newv(n);

		 	gettimeofday(&b, NULL);
		 	mergeSort(v, 0, n-1);
		 	gettimeofday(&a, NULL);

		 	tempo  += tvtosec(a) - tvtosec(b);
		 	free(v);
	 	}
        fprintf(stderr, "%d %10lf\n", n, tempo/3000 );
	 	printf("%d %10lf\n", n, tempo/3000);
	 }

 	return 0;

 }


void *merge(int *vetor, int comeco, int meio, int fim) {
    int i = comeco;
    int j = meio+1, k=0;;
    int *aux = (int *) malloc((fim-comeco+1) * sizeof(int));

    while (k <= fim-comeco){
        if ((vetor[i] < vetor[j] && i <= meio) || (j > fim)){
            aux[k] = vetor[i];
            i++;
        }else{
            aux[k] = vetor[j];
            j++;
        }
        k++;
    }
    k = 0;

    while (k <= fim-comeco){
        vetor[comeco+k] = aux[k];
        k++;
    }
    free(aux);
}

void *mergeSort(int *vetor, int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, comeco, meio, fim);
    }
}


int *newv (unsigned int n){

  int *v =  (int*)malloc(n*sizeof(int));
  for(int i = 0; i < n; i++) v[i] = rand() % 11;


  return v;

}

double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}