
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/* estrutura */
typedef struct tree{
    struct tree *p;
    struct tree *r;
    struct tree *l;
    int v;
    unsigned int h;
}Tree;


/* assinaturas das funções */
Tree* newnode(int num);
void adicionar(Tree **raiz, int v, Tree* pai, Tree** RaizOriginal);
void tprint( Tree* x);
void verifica(Tree* n, Tree** RaizOriginal);
int mod(int i);
unsigned int alturaArvore(Tree *a);
unsigned int maxAlt(int no1, int no2);
void balancear(Tree* n, Tree** RaizOriginal);
void re(Tree* x);
void rd(Tree* x);
int buscar(Tree* raiz, int n);
double tvtosec(struct timeval t);
void tremove(Tree* x);


/* função principal */
int main (void) {
    Tree* raiz = NULL;
    srand(time(NULL));
	struct timeval a;
	struct timeval b;
	double tempo;
    int i, aleatorio, k, n, achou;



/* CONTROLA O TAMANHO */

 	for(n = 10000; n <= 100000; n += 10000){      
        for(k = 1; k <= n; k++){
           /* adicionar(&raiz, k, NULL, &raiz); pior caso */

            aleatorio = rand() % k;
            if(buscar(raiz, aleatorio) != 1)
                adicionar(&raiz, aleatorio, NULL, &raiz); /* caso médio */
        }
        
 		tempo = 0;

        /* CALCULA A MEDIA */
 		for(i = 0; i < 1000 ; i++){

		 	gettimeofday(&b, NULL);
             
            /* achou = buscar(raiz, 1); /* pior caso */
            achou = buscar(raiz, rand() % k); /* caso médio */

		 	gettimeofday(&a, NULL);
		 	tempo  += tvtosec(a) - tvtosec(b);
	 	}

        tremove(raiz);
        raiz = NULL;

        /* PRINTA O RESULTADO */

	 	fprintf(stderr, "%d %.20lf\n", n, tempo/1000 );
	 	printf("%d %.20lf\n", n, tempo/1000 );

     }

    /* testes manuais

    adicionar(&raiz, 3, NULL, &raiz);
    adicionar(&raiz, 29, NULL, &raiz);
    adicionar(&raiz, 46, NULL, &raiz);
    adicionar(&raiz, 35, NULL, &raiz);
    adicionar(&raiz, 33, NULL, &raiz);
    adicionar(&raiz, 37, NULL, &raiz);
    adicionar(&raiz, 28, NULL, &raiz);
    adicionar(&raiz, 10, NULL, &raiz);
    adicionar(&raiz, 15, NULL, &raiz);
    adicionar(&raiz, 24, NULL, &raiz);
    
    tprint(raiz);
    
    */
}


void adicionar(Tree **raiz, int v, Tree* pai, Tree** raizOriginal){

    /* cria um novo nó com o valor */
    Tree *n = newnode(v);

    /* verifica se a raiz é nula */
    if(*raiz == NULL){

        /* se for nula o pai vai ser a última antes dela */
        n->p = pai;
        /* a raiz recebe o nó */
        *raiz = n;
        /* e por último, verifica se  existe algum desbalanceamento */
        verifica(n, raizOriginal);   
             
    }

    /* caso em que o número adicinado é maior chama a função recursivamente enviando o lado esquerdo, o numero, o pai e a raiz original */
    else if ((*raiz)-> v > n->v){
        adicionar(&((*raiz)-> l),n->v,*raiz,raizOriginal);

    /* caso em que o número adicinado é menor */
    }else{
        adicionar(&((*raiz)-> r),n->v,*raiz,raizOriginal);
    }
} 

/* função para criar um nó */

Tree* newnode(int num){

    Tree* a = (Tree*)malloc(sizeof(Tree));
    a->v = num;
    a->l = NULL;
    a->r = NULL;
    a->p = NULL;
    a->h = 1;
    return a;

}

/* função para imprimir informações da arvore */

void tprint( Tree* x){
    if(x != NULL){
        tprint(x->l);
        printf("Endereço: %p Valor: %d Esquerda: %p Direita: %p Pai: %p  altura: %d\n", x , x->v, x->l, x->r, x->p, x->h);
        tprint(x->r);
    }
}

/* função para verificar se há desbalanceamento e fazer update da altura dos nós */
void verifica(Tree* n, Tree** RaizOriginal){

    /* laço para verificar desbalanceamentos */
   
    while (n != NULL){

        /* já atualiza a altura em toda passagem (já que foi inserido um elemento, as alturas irão mudar) */
        n->h =(alturaArvore(n));
        
        /* após atualizadas as alturas verifica se há desbalanceamento, se houver chamar função para balancear */
        if (mod(alturaArvore(n->r) - alturaArvore(n->l)) > 1) {
            printf("\n>> Entrei no balanceamento <<\n\n");
            balancear(n,RaizOriginal); 
        }

        /* verifica o pai (proximo) */
        n = n->p;   
    }
}

/* função para retornar o módulo de um número */

int mod(int i){

    return i > 0 ? i : -i;

}

/* função recursiva para comparar qual o lado mais pesado */

unsigned int alturaArvore(Tree *a){
	if (a == NULL) return 0;
    return maxAlt(alturaArvore(a->l), alturaArvore(a->r)) + 1;
}

/* função para verificar qual número é maior */
unsigned int maxAlt(int no1, int no2){

    return (no1 > no2 ) ? no1 : no2;

}

/* função que verifica o caso (1,2,3,4) para poder fazer a rotação */

void balancear(Tree* n, Tree** RaizOriginal){

    /* verificando a diferença de alturas */
	int dp = alturaArvore(n->r) - alturaArvore(n->l);
	int df;
	
    if(n->h != dp){

        /* casos 1 ou 3 */
        if (dp == 2){

            /* verificando se é caso 1 ou 3 */
            df = alturaArvore(n->r->r) - alturaArvore(n->r->l);

            /* caso 3 */
            if (df == -1){

                printf("\n\n>> Entrei no caso 3 <<\n\n");

                /* fazendo a primeira rotação */

                rd(n->r);

                /* atualizando a altura apos a primeira rotação */

                int aux = n->r->h;
                n->r->h = n->r->r->h;
                n->r->r->h = aux;
                
                /* fazendo a segunda rotação */

                re(n);
               
                if (n == *RaizOriginal)
                    *RaizOriginal = n->p;

                /* atualizando a altura */

                n->h =( alturaArvore(n));
            
            /* caso 1 */

            } else {

                printf("\n\n>> Entrei no caso 1 <<\n\n");

                re(n);

                if (n == *RaizOriginal)						    
                    *RaizOriginal = n->p;

                n->h =(alturaArvore(n));
                
            }
        }

        /* casos 2 ou 4 */
        else if (dp == -2) {

            /* verificando se é caso 2 ou 4 */

            df = alturaArvore(n->l->r) - alturaArvore(n->l->l);

            /* caso 2 */

            if (df <= 0){
                
                printf("\n\n>> Entrei no caso 2 <<\n\n");

                rd(n);
                if (n == *RaizOriginal)
                    *RaizOriginal = n->p;
                
                n->h =( alturaArvore(n));

            /* caso 4 */
            } else {

                printf("\n\n>> Entrei no caso 4 <<\n\n");

                /* fazendo a primeira rotação */

                re(n->l);
                
                /* atualizando a altura apos a primeira rotação */

                int aux = n->l->h;
                n->l->h = n->l->l->h;
                n->l->l->h = aux;

                /* fazendo a segunda rotação */

                rd(n);
               
                if (n == *RaizOriginal)
                    *RaizOriginal = n->p;

                /* atualizando a altura */

                n->h =( alturaArvore(n));
         
            }
        }
    }
}


/* função que faz a rotação na esquerda */

void re(Tree* x){
    printf("\n\n>> Entrei na rotação da esquerda <<\n\n");
    Tree *y = x->r;
    Tree *b = y->l;

    if(x->p != NULL){
        if(x->p->r == x){
            x->p->r = y;
        }else{
            x->p->l = y;
        }
    }
    y->p = x->p;
    x->p = y;
    y->l = x;
    if(b!=NULL)
		b->p = x;
    x->r = b;
}


/* função que faz a rotação na direita */

void rd(Tree* x){
    printf("\n\n!-- Entrei na rotação da direita --!\n\n");
    Tree *y = x->l;
    Tree *b = y->r;

    if(x->p != NULL){
        if(x->p->l == x){
            x->p->l = y;
        }else{
            x->p->r = y;
        }
    }
    y->p = x->p;
    x->p = y;
    y->r = x;
	if(b!=NULL)
		b->p = x;
    x->l = b; 
}


/* função para procurar um elemento na arvore */
int buscar(Tree* raiz,int n){

    if(raiz == NULL) return 0;

    if(raiz->v == n)
        /* achou */
        return 1;
    
    else if ((raiz)->v > n)
        return buscar((raiz->l),n);
    
    else
        return buscar((raiz->r),n);
    
    return 0;
}

/* função para converter o tempo */
double tvtosec(struct timeval t){
  return (double) t.tv_sec + t.tv_usec/(double)1e6;

}


/* função para liberar arvore */
void tremove(Tree* x){

    if(x != NULL){
        tremove(x->l);
        tremove(x->r);
        free(x);
    }

    return;
}
