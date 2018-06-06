
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int sorted(int *v, int n);
void *bogo(int *v, int n);
void *shuffle(int *v, int n);
int *newv (unsigned int n);



int main(void) 
 {

	srand(time(NULL)); 
	struct timeval a;
	struct timeval b;
	double tempo;
	int n;

 	for(n = 3; n <= 13; n++){
 		tempo = 0;
		int *v = newv(n);
		gettimeofday(&b, NULL);
		bogo(v, n);
		gettimeofday(&a, NULL);
		tempo = tvtosec(a) - tvtosec(b);
		free(v);
	 	fprintf(stderr, "%d %10lf\n", n, tempo);
	 	printf("%d %10lf\n", n, tempo);
	}
 	return 0;
 }

 void *bogo(int *v, int n){
     while(sorted(v,n) != 1){
        shuffle(v,n);
     }
 }

void *shuffle(int *v, int n){
	int a, aux, i =0;
    for(i; i < n; i++){
		a = rand() % n;
		aux = v[i];
		v[i] = v[a];
		v[a] = aux;    
    }
    return v;
}

int sorted(int *v, int n){
    int i =0;
    for(i; i < n-1; i++){
        if(v[i] > v[i+1]){
            return 0;
        }
    }
    return 1;
}

double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}


 int *newv (unsigned int n){

  int *v =  (int*)malloc(n*sizeof(int));
  for(int i = 0; i < n; i++) v[i] = rand() % n;


  return v;

}