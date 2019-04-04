
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv (unsigned int n);
int *distribution (int *v, int n);
int *new_0 (unsigned int n);
int min(int *v, int n);
int max(int *v, int n);


int main(void) 
 {

	srand(time(NULL)); 
	struct timeval a;
	struct timeval b;
	double tempo;
	int *ordenado;

 	for(int n = 1000; n <= 10000; n += 100){

 		tempo = 0;

 		for(int i = 0; i < 1000 ; i++){
 
		 	int *v = newv(n);

		 	gettimeofday(&b, NULL);
		 	ordenado = distribution(v, n);
		 	gettimeofday(&a, NULL);

		 	tempo  += tvtosec(a) - tvtosec(b);
		 	free(v);
	 	}

	 	printf("%d %10lf\n", n, tempo/1000);
	 	fprintf(stderr, "%d %10lf\n", n, tempo/1000 );

	 }

 	return 0;

 }

 int *distribution (int *v, int n){
 	int l = min(v,n);
 	int b = max(v,n);
 	int k = b-l+1;
 	int i, j;
 	int *w = new_0(k);
 	int *y = new_0(n);

     for (i = 0;i < n ;i++){
          w[v[i]-l]++;
     }

     for (j = 1; j <= b-l;j++){
         w[j] = w[j] + w[j-1];
     }

     for (i = 0;i <= n-1; i++){
         j = w[v[i]- l];
         y[j-1] = v[i];
         w[v[i]-l]--;
     }

 	return y;
 	free(y);
 	free(w);
 }

 int *newv (unsigned int n){

  int *v =  (int*)malloc(n*sizeof(int));
  for(int i = 0; i < n; i++){ v[i] = rand() % n ;}


  return v;

}

 int *new_0 (unsigned int n){

  int *v =  (int*)malloc(n*sizeof(int));
  for(int i = 0; i < n; i++) v[i] = 0;


  return v;

}

double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}

int min(int *v, int n){
	int menor;
	for(int i = 0; i < n; i++){
		if(i == 0){
			menor = v[i];
		}else{
			if(v[i] < menor){
				menor = v[i];
			}
		}
	}

	return menor;
}

int max(int *v, int n){
	int maior;
	for(int i = 0; i < n; i++){
		if(i == 0){
			maior = v[i];
		}else{
			if(v[i] > maior){
				maior = v[i];
			}
		}
	}

	return maior;
}

