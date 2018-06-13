
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef struct node {
    
    int v;
    struct node *l;
    struct node *r;

}Node;

void adicionar(Node **node, int v);
int tsearch(Node* x, int v);
Node* newnode(int num);
int *newv (unsigned int n);
double tvtosec(struct timeval t);
void tprint(Node* x);
void tremove(Node* x);


/* main de calcular o tempo */

/* 
    "pior caso": preenchendo de forma crescente e procurando por n (ultimo valor)
    "caso medio": preenchendo de forma aleatoria e procurando um numero aleatorio
*/
 
 
int main (void){

    Node *node = NULL;
	srand(time(NULL)); 
	struct timeval a;
	struct timeval b;
	double tempo;
    int achou;
    int n, k, i;


    /* CONTROLA O TAMANHO */

 	for(n = 1000; n <= 10000; n += 500){      

        
 		tempo = 0;


        /* CALCULA A MEDIA */
 		for(i = 0; i < 5000 ; i++){
            
            /* PREENCHE A ÁRVORE */

            for(k = 0; k < n; k++){
                adicionar(&node, (rand() % (k+1)));
            }

		 	gettimeofday(&b, NULL);

            achou = tsearch(node, (n*2)); /* pior caso */
            /* achou = tsearch(node, (rand() % (n+1))); /* caso  médio*/
		 	gettimeofday(&a, NULL);

		 	tempo  += tvtosec(a) - tvtosec(b);

            /* LIBERA A ARVORE */
            
            tremove(node);
            node = NULL;
	 	}

        /* PRINTA O RESULTADO */

	 	fprintf(stderr, "%d %.20lf\n", n, tempo/5000 );
	 	printf("%d %.20lf\n", n, tempo/5000 );


	}

    return 0;

}


void adicionar(Node **n, int v) {

    Node *aux, *f;

    if(*n == NULL){
        (*n) = newnode(v);
    }else{
        aux = *n;
        while(aux != NULL){
            f = aux;
            if(aux->v < v){
                aux = aux->r;
            }else{
                aux = aux->l;
            }
        }

      (f->v < v) ? (f->r = newnode(v)) : (f->l = newnode(v));
    }
}


int tsearch(Node* x, int v){
    if(x != NULL){
        if(x->v == v){
            return 1;
        }else if(x->v < v){
            return tsearch(x->r, v);
        }else{ 
            return tsearch(x->l,v);
        }
    }else{
        return 0;
    }

}

Node* newnode(int num){

    Node* a = (Node*)malloc(sizeof(Node));

    a->v = num;
    a->l = NULL;
    a->r = NULL;

    return a;

}


double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}


void tprint(Node* x){
    
    if(x != NULL){
        tprint(x->l);
        printf("%p %d %p %p \n", x , x->v, x->l, x->r);
        tprint(x->r);
    }

}

void tremove(Node* x){

    if(x != NULL){
        tremove(x->l);
        tremove(x->r);
        free(x);
    }

    return;

}
