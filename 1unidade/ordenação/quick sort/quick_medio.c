
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>



int *newv (int n);
double tvtosec(struct timeval t);
void quickSort(int *v, int s, int e);
int partition(int *v, int s, int e);

int main(void) 
 {

  srand(time(NULL)); 
  struct timeval a;
  struct timeval b;
  double tempo;
  int n,i;


  for(n = 1000; n <= 10000; n+= 100){
      tempo = 0;

      for(i = 0; i < 500; i++){

   
        int *v = newv(n);
        gettimeofday(&b, NULL);
        quickSort(v, 0, n-1);
        gettimeofday(&a, NULL);
        tempo  += tvtosec(a) - tvtosec(b);
        free(v);
      }
      
    fprintf(stderr, "%d %10lf\n", n, tempo/500 );
    printf("%d %10lf\n", n, tempo/500);
  }

  return 0;

 }


void quickSort(int *v, int s, int e){
  int p;
  if(s < e){
    p = partition(v,s,e);
    quickSort(v,s, p-1);
    quickSort(v,p+1, e);
  }
}

int partition(int *v, int s, int e){
  int l = s, i , aux;
  for(i=s; i<e; i++){
    if(v[i]<v[e]){
      aux= v[i];
      v[i] = v[l];
      v[l] = aux;
      l++;
    }
  }
  aux = v[e];
  v[e] = v[l];
  v[l] = aux;
  return l;
}


int *newv (int n){
  /* no caso médio o vetor é preenchido de forma aleatória */

  int *v =  (int*)malloc(n*sizeof(int));
  for(int i = 0; i < n; i++)
  { v[i] = rand() % n;}


  return v;

}

double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}

