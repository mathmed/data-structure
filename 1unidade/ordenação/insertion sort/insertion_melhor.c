
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv (unsigned int n);
void ordena (int *vetor, unsigned int n);

int main( void ) {

	srand(time(NULL)); 
	struct timeval a;
	struct timeval b;
	double tempo;

	int i, j, atual, *vetor, n;


	for(n = 1000; n <= 10000; n += 100){

		tempo = 0;

		 for(i = 0; i < 30000 ; i++){

		 	vetor = newv(n);
			
			gettimeofday(&b, NULL);

			ordena(vetor, n);

			gettimeofday(&a, NULL);

	        tempo  += tvtosec(a) - tvtosec(b);
	      	free(vetor);
	    }
	 	fprintf(stderr, "%d %10lf\n", n, tempo/30000 );
		printf("%d %10lf\n", n, tempo/30000);
	}
	return 0;

}

double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}

int *newv (unsigned int n){

  /* melhor caso o vetor é preenchido em ordem crescente (ja está ordenado) */

  int *v =  (int*)malloc(n*sizeof(int));
  for(int i = 0; i < n; i--) v[i] = i+1;


  return v;

}

void ordena (int *vetor, unsigned int n){

	int i, j, atual;

	for (i = 1; i < n; i++) {

		atual = vetor[i]; 

		for (j = i - 1; (j >= 0) && (atual < vetor[j]); j--) { 
			vetor[j+1] = vetor[j];
	    }

		vetor[j+1] = atual;
	}

}