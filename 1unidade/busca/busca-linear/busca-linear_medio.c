
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>



int *newv (int n);
double tvtosec(struct timeval t);
int search(int *v, int n, int x);

int main(void) 
 {

  srand(time(NULL)); 
  struct timeval a;
  struct timeval b;
  double tempo;
  int n,i;


  for(n = 10000; n <= 100000; n+= 1000){
      tempo = 0;

      for(i = 0; i < 10000; i++){

   
        int *v = newv(n);
        gettimeofday(&b, NULL);
        int achou = search(v, n-1, rand() % n+2); /* caso médio o número procurado pode ou não está no vetor */
        gettimeofday(&a, NULL);
        tempo  += tvtosec(a) - tvtosec(b);
        free(v);
      }
      
    fprintf(stderr, "%d %10lf\n", n, tempo/10000 );
    printf("%d %10lf\n", n, tempo/10000);
  }

  return 0;

 }


 int search(int *v, int n, int x){

  int i;
  for (i = 0; i < n; i++)
  {
    if(v[i] == x){
      return i;
    }
  }

  return -1;

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

