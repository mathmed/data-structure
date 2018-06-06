
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv (unsigned int n);
void *bubble (int *v, int n);

int main(void) 
 {

	srand(time(NULL)); 
	struct timeval a;
	struct timeval b;
	double tempo;

 	for(int n = 1000; n <= 10000; n += 100){

 		tempo = 0;

 		for(int i = 0; i < 100 ; i++){
 
		 	int *v = newv(n);

		 	gettimeofday(&b, NULL);
		 	bubble(v, n);
		 	gettimeofday(&a, NULL);

		 	tempo  += tvtosec(a) - tvtosec(b);
		 	free(v);
	 	}

	 	fprintf(stderr, "%d %10lf\n", n, tempo/100 );
	 	printf("%d %10lf\n", n, tempo/100);
	 }

 	return 0;

 }

 void *bubble (int *v, int n){
  int aux, i, j;
  for(i = 0; i < n; i++){
    for(j =0; j < n; j++){
      if(v[i] < v[j]){
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
      }
    }
  }

 }


 int *newv (unsigned int n){

  int *v =  (int*)malloc(n*sizeof(int));
  for(int i = 0; i < n; i++) v[i] = rand() % n;


  return v;

}

double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}