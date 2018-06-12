
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/* iniciando a estrutura */

typedef struct lista {
    int numero;
    struct lista *prox;
}Lista;

/* assinatura das funções */

Lista* criar_no(int num);
void adicionar(Lista **raiz, int num);
void print(Lista *raiz);
int buscar(Lista *raiz, int num);
void tremove(Lista *raiz);
double tvtosec(struct timeval t);


int main (void) {

    /* iniciando a raiz */
    Lista *raiz = NULL;
    srand(time(NULL));
	struct timeval a;
	struct timeval b;
	double tempo;
    int i, aleatorio, k, n, achou;

    /* CONTROLA O TAMANHO */

 	for(n = 10000; n <= 100000; n += 10000){      
        for(k = 1; k <= n; k++){
            /* adicionando na lista */
            adicionar(&raiz, k);
        }
        
 		tempo = 0;

        /* CALCULA A MEDIA */
 		for(i = 0; i < 10000 ; i++){

		 	gettimeofday(&b, NULL);
            /* achou = buscar(raiz, -1); /* pior caso */
            achou = buscar(raiz, rand() % k); /* caso medio */
		 	gettimeofday(&a, NULL);
		 	tempo  += tvtosec(a) - tvtosec(b);
	 	}

        tremove(raiz);
        raiz = NULL;

        /* PRINTA O RESULTADO */

	 	fprintf(stderr, "%d %.20lf\n", n, tempo/10000 );
	 	printf("%d %.20lf\n", n, tempo/10000 );

    }

    
}


/* função para criar um nó da lista */

Lista* criar_no(int num){

    Lista* no = (Lista*)malloc(sizeof(Lista));
    no->numero = num;
    no->prox = NULL;
    return no;

}

/* função para adicionar elemento à lista */
void adicionar(Lista **raiz, int num){

    Lista* no = criar_no(num);

   /* número adicionado sempre fica na primeira posição */

    no->prox = (*raiz);
    *raiz = no;

        

}


/* função para printar lista */
void print(Lista *raiz){

    if(raiz != NULL){
        printf("\nEndereço: %p Valor: %d Próximo nó: %p\n", raiz, raiz->numero, raiz->prox);
        print(raiz->prox);
    }

}


/* função para buscar elemento na lista */

int buscar(Lista *raiz, int num){
    
    if(raiz == NULL) return 0;

    else if (raiz->numero == num) return 1;

    else buscar(raiz->prox, num);

}

/* função para liberar a lista */

void tremove(Lista *raiz){
    if(raiz != NULL){
        tremove(raiz->prox);
        free(raiz);
    }

    return;
}

/* função para converter o tempo */
double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}
