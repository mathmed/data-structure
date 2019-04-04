
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>



int *newv (int n);
double tvtosec(struct timeval t);
 int search(int *v, int s, int e, int k);

int main(void) 
 {

  srand(time(NULL)); 
  struct timeval a;
  struct timeval b;
  double tempo;
  int n,i;


  for(n = 10000; n <= 100000; n+= 1000){
      tempo = 0;

      for(i = 0; i < 20000; i++){

          
        int *v = newv(n);
        int procurar = rand() % n;
        gettimeofday(&b, NULL);
        int achou = search(v, 0, n-1, procurar); /* caso médio será procurado um número aleatório dentro do vetor */
        gettimeofday(&a, NULL);
        tempo  += tvtosec(a) - tvtosec(b);
        free(v);
      }
      
    fprintf(stderr, "%d %.15lf\n", n, tempo/20000 );
    printf("%d %.15lf\n", n, tempo/20000);
  }

}

 int search(int *v, int s, int e, int k){

  int m = (s+e)/2;
  if(s <= e){
    if(v[m] == k){
      return m;
    }else if (v[m] > k){
      search(v, s, m-1, k);
    }else{
      search(v, m+1, e, k);
    }
  }else{
    return -1;
  }

 }


 int *newv (int n){

  int *v =  (int*)malloc(n*sizeof(int));
  for(int i = 0; i < n; i++)
  { v[i] = i+1;}


  return v;
}


double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}

