
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


/* função prncipal */
int main (void) {
    Tree* raiz = NULL;
    srand(time(NULL));
	struct timeval a;
	struct timeval b;
	double tempo;
    int achou;
    int n, k, i;


    /* CONTROLA O TAMANHO */

 	for(n = 10000; n <= 100000; n += 10000){      
        for(k = 0; k < n; k++){
            adicionar(&raiz, k+1, NULL, &raiz ); /* pior caso */
            /* adicionar(&raiz, rand() % (k+1)); /* caso médio */
        }
        
 		tempo = 0;

        /* CALCULA A MEDIA */
 		for(i = 0; i < 5000 ; i++){

		 	gettimeofday(&b, NULL);

            achou = buscar(raiz, k+2); /* pior caso */
            /* achou = buscar(raiz, rand() % (k+1)); /* caso  médio*/
		 	gettimeofday(&a, NULL);
		 	tempo  += tvtosec(a) - tvtosec(b);
	 	}

        tremove(raiz);
        raiz = NULL;

        /* PRINTA O RESULTADO */

	 	fprintf(stderr, "%d %.20lf\n", n, tempo/5000 );
	 	printf("%d %.20lf\n", n, tempo/5000 );

	}
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
        /* e por último verifica se  existe algum desbalanceamento */
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
    a->h = 0;
    return a;

}

/* função para imprimir informações da arvore */

void tprint( Tree* x){
    if(x != NULL){
        tprint(x->l);
        printf("Endereço: %p Valor: %d Esquerda: %p Direita: %p Pai: %p \n", x , x->v, x->l, x->r, x->p);
        tprint(x->r);
    }
}

/* função para verificar se há desbalanceamento */
void verifica(Tree* n, Tree** RaizOriginal){

    /* laço que começa no ultimo elemento adicionado e vai até a raiz da arvore */
    while (n != NULL)
    {
        /* verifica se há desbalanceamento nas alturas, se houver chamar função para balancea */
        if (mod(alturaArvore(n->r) - alturaArvore(n->l)) > 1) balancear(n,RaizOriginal);

        /* atribui altura e verifica o pai (proximo) */
        n->h = alturaArvore(n);
        n = n->p;
    }
}

/* função para retornar o módulo de um número */

int mod(int i){

    return i > 0 ? i : -i;

}

/* função recursiva para verificar qual o lado mais pesado da arvore */

unsigned int alturaArvore(Tree *a){
	if (a == NULL) return 0;
    return maxAlt(alturaArvore(a->l), alturaArvore(a->r)) + 1;
}

/* função para verificar qual número é maior */
unsigned int maxAlt(int no1, int no2){

    return (no1 > no2 ) ? no1 : no2;

}


/* função que verifica o caso para poder fazer a rotação */

void balancear(Tree* n, Tree** RaizOriginal){
    /* verificando a diferença */
	int dp = alturaArvore(n->r) - alturaArvore(n->l);
	int df;
	
    /* casos 1 e 3 */
    if (dp == 2){

        /* verificando se é caso 1 ou 3 */
		df = alturaArvore(n->r->r) - alturaArvore(n->r->l);

        /* caso 3 */
        if (df == -1){
            
            /* faz duas rotações na arvore */
            re(n);
            re(n);
		    if (n == *RaizOriginal)
                *RaizOriginal = n->p;

        /* caso 1 */
        } else {

            /* faz uma rotação na arvore */
            re(n);
			if (n == *RaizOriginal)						    
                *RaizOriginal = n->p;
            
        }
	}

    /* casos 2 e 4 */
    else if (dp == -2) {

        /* verificando se é caso 2 ou 4 */
        df = alturaArvore(n->l->r) - alturaArvore(n->l->l);

        /* caso 2 */
        if (df <= 0){

            /* faz uma rotação na arvore */
            rd(n);
                if (n == *RaizOriginal)
                    *RaizOriginal = n->p;
                

        /* caso 4 */
        } else {

            /* faz duas rotações na arvore */
            rd(n);
            rd(n);
            if (n == *RaizOriginal)
                *RaizOriginal = n->p;
	    }
    }   
}


/* função que faz a rotação na esquerda */

void re(Tree* x){
    Tree* pai = x->p;
    Tree* b = x->r;
    Tree* c = x->r->l;
    b->p = pai;
    if(pai != NULL){
        if(pai->l == x)
            pai->l=b;
        
        else
            pai->r=b;
        
    }
    x->r=c;
    b->l=x;
    x->p=b;

    if(c!=NULL)
        c->p=x;
    

    /* atualizando as alturas */
    x->h = alturaArvore(x);
    b->h = alturaArvore(b);  		
}


/* função que faz a rotação na direita */

void rd(Tree* x){
    Tree* pai = x->p;
    Tree* b = x->l;
    Tree* c = x->l->r; 
    
    b->p = pai;

    if(pai != NULL){
        if(pai->r == x)
            pai->r=b;
        else
            pai->l=b;
        
    }

    x->l=c;
    b->r=x;
    x->p=b;
   
  if(c!=NULL)
        c->p=x;
    

    /* atualizando as alturas */
    x->h = alturaArvore(x);
    b->h = alturaArvore(b);  
}


/* função para procurar um elemento na arvore */
int buscar(Tree* raiz,int n){

    if(raiz == NULL) return 0;

    if(raiz == NULL || raiz->v == n)
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
