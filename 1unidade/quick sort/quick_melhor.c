
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
void *fill(int *v, int s, int e);

int main(void) 
 {

  srand(time(NULL)); 
  struct timeval a;
  struct timeval b;
  double tempo;
  int n,i;

  for(n = 1000; n <= 10000; n+= 100){
      tempo = 0;

      for(i = 0; i < 2000; i++){

   
        int *v = newv(n);
        fill(v,0, n-1);
        gettimeofday(&b, NULL);
        quickSort(v, 0, n-1);
        gettimeofday(&a, NULL);
        tempo  += tvtosec(a) - tvtosec(b);
        free(v);
      }
      
    fprintf(stderr, "%d %10lf\n", n, tempo/2000 );
    printf("%d %10lf\n", n, tempo/2000);
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

  int *v =  (int*)malloc(n*sizeof(int));
  for(int i = 0; i < n; i++)
  { v[i] = i+1;}


  return v;

}

/* preencher o vetor para o melhor caso */

void *fill(int *v, int s, int e){

  int m = (s+e)/2;
  if(e-s+1 == 3){
    v[e] = m+1;
    v[s] = m;
    v[s+1] = m+2;
  }else if(e-s+1 > 3){
    fill(v,s,m-1);
    fill(v,m+1,e);
    v[m] = v[e];
    v[e] = m+1;
  }
}

double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}

