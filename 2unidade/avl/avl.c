
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
    int n, k, i, aleatorio;



    /* teste com números aleatórios */

    for(i = 1; i <= 15; i++){
        aleatorio = rand() % 30;
        if(buscar(raiz, aleatorio) != 1){
            printf("\n - adicionando %d - \n", aleatorio);
            adicionar(&raiz, aleatorio, NULL, &raiz);
        }
    }

    tprint(raiz);



    /* teste de casos base 

    adicionar(&raiz, 30, NULL, &raiz);

    adicionar(&raiz,20, NULL, &raiz);

    adicionar(&raiz, 25, NULL, &raiz); 

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

/* função para verificar se há desbalanceamento */
void verifica(Tree* n, Tree** RaizOriginal){

    /* laço que começa no ultimo elemento adicionado e vai até a raiz da arvore */
   
    while (n != NULL)
    {

        n->h =(alturaArvore(n));
        
        /* verifica se há desbalanceamento nas alturas, se houver chamar função para balancer */
        if (mod(alturaArvore(n->r) - alturaArvore(n->l)) > 1) {
            printf("\n!--Entrei no balanceamento--!\n\n");
            balancear(n,RaizOriginal); 
        }

        /* atribui altura e verifica o pai (proximo) */
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


/* função que verifica o caso para poder fazer a rotação e atualizar as alturas depois */

void balancear(Tree* n, Tree** RaizOriginal){
    /* verificando a diferença */
	int dp = alturaArvore(n->r) - alturaArvore(n->l);
	int df;
	
    if(n->h != dp){
        /* casos 1 e 3 */
        if (dp == 2){
            

            /* verificando se é caso 1 ou 3 */
            df = alturaArvore(n->r->r) - alturaArvore(n->r->l);

            /* caso 3 */
            if (df == -1){
                 printf("\n\n!-- Entrei no caso 3 --!\n\n");
                /* entrou no caso 3 */

                rd(n->r);

                /* atualizando a altura apos a primeira rotação manualmente */
                int aux = n->r->h;
                n->r->h = n->r->r->h;
                n->r->r->h = aux;

                re(n);
               
                
                if (n == *RaizOriginal)
                    *RaizOriginal = n->p;

                n->h =( alturaArvore(n));
            
            /* caso 1 */
            } else {
                printf("\n\n!-- Entrei no caso 1 --!\n\n");

                re(n);
                if (n == *RaizOriginal)						    
                    *RaizOriginal = n->p;

                n->h =( alturaArvore(n));
                
                
            }
        }

        /* casos 2 e 4 */
        else if (dp == -2) {

            /* verificando se é caso 2 ou 4 */
            df = alturaArvore(n->l->r) - alturaArvore(n->l->l);

            /* caso 2 */
            if (df <= 0){
                
                printf("\n\n!-- Entrei no caso 2 --!\n\n");

                rd(n);
                    if (n == *RaizOriginal)
                        *RaizOriginal = n->p;
                
                n->h =( alturaArvore(n));

            /* caso 4 */
            } else {

                printf("\n\n!-- Entrei no caso 4 --!\n\n");

                re(n->l);
                
                 /* atualizando a altura apos a primeira rotação manualmente */
                int aux = n->l->h;
                n->l->h = n->l->l->h;
                n->l->l->h = aux;

                rd(n);
               
                if (n == *RaizOriginal)
                    *RaizOriginal = n->p;

                n->h =( alturaArvore(n));

                    
            }
        }
    }
}


/* função que faz a rotação na esquerda */

void re(Tree* x){
    printf("\n\n!-- Entrei na rotação da esquerda --!\n\n");
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
