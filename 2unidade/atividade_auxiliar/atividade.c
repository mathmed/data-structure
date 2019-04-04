
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/* ESTRUTURA DA ÁRVORE */
typedef struct tree{
    struct tree *p;
    struct tree *r;
    struct tree *l;
    int v;
    unsigned int h;
}Tree;

/* ESTRUTURAS DAS TABELA HASH */
typedef struct bloco{
      int valor;
      struct bloco *proximo;
}Bloco;

/* STRUCT QUE SIMULA O VETOR */
typedef struct table{
      unsigned int tam;
      unsigned int n;
      struct bloco **b;
}Table;

/* assinaturas das funções da árvore */
Tree* newnode(int num);
void adicionar_na_arvore(Tree **raiz, int v, Tree* pai, Tree** RaizOriginal);
void tprint( Tree* x);
void verifica(Tree* n, Tree** RaizOriginal);
int mod(int i);
unsigned int alturaArvore(Tree *a);
unsigned int maxAlt(int no1, int no2);
void balancear(Tree* n, Tree** RaizOriginal);
void re(Tree* x);
void rd(Tree* x);
void tremove(Tree* x);

/* assinaturas das funções da tabela */
Bloco* novo(int );
unsigned int hash(int a, int b);
void tremoveTabela(Table* table);
void tremoveBloco(Bloco* bloco);
void update_tam(Table* table);
void adicionar(Table* table , Bloco* bloco );
void exibiLista(Bloco *x);
void exibiTabela(Table *t);
void atualizar(Table *table);

/* assinatura da função da atividade */
void remove_da_arvore_adiciona_na_tabela(Tree *arvore, Table *table);

/* função principal */
int main (void) {

    /* auxiliares */
    srand(time(NULL));
    int i, aleatorio;

    /* iniciando a árvore */
    Tree* raiz = NULL;

    /* iniciando a tabela */
    Table table;
    table.b = malloc(sizeof(Bloco*)*(1));
	table.n = 0;
	table.tam = 1;

    /* adicinando elementos na árvore */

    for(i = 0; i < 15; i++){
        aleatorio = rand() % 100;
        adicionar_na_arvore(&raiz, aleatorio, NULL, &raiz);
    }

    /* ORDEM QUE COLOQUEI NA PROVA 
    adicionar_na_arvore(&raiz, 20, NULL, &raiz);
    adicionar_na_arvore(&raiz, 4, NULL, &raiz);
    adicionar_na_arvore(&raiz, 30, NULL, &raiz);
    adicionar_na_arvore(&raiz, 11, NULL, &raiz);
    adicionar_na_arvore(&raiz, 2, NULL, &raiz);
    adicionar_na_arvore(&raiz, 5, NULL, &raiz);
    adicionar_na_arvore(&raiz, 7, NULL, &raiz);
    adicionar_na_arvore(&raiz, 12, NULL, &raiz);
    adicionar_na_arvore(&raiz, 14, NULL, &raiz);
    adicionar_na_arvore(&raiz, 23, NULL, &raiz);
    adicionar_na_arvore(&raiz, 28, NULL, &raiz);
    adicionar_na_arvore(&raiz, 15, NULL, &raiz);
    adicionar_na_arvore(&raiz, 19, NULL, &raiz);
    adicionar_na_arvore(&raiz, 10, NULL, &raiz);
    adicionar_na_arvore(&raiz, 1, NULL, &raiz);
    */

    tprint(raiz);

    /* chamando a função que remove da árvore e insere na árvore */

    remove_da_arvore_adiciona_na_tabela(raiz, &table);

    /* exibindo a tabela */
    printf("\n\n");
    exibiTabela(&table);
    
    return 0;

}


/********************** FUNÇÃO PARA REMOVER DA ÁRVORE E INSERIR NA TABELA **************************/

void remove_da_arvore_adiciona_na_tabela(Tree *arvore, Table *table){

    /* auxiliar para guardar o valor da arvore */

    int auxiliar;

    if(arvore != NULL){

        /* recursão até chegar no fim da arvore */
        remove_da_arvore_adiciona_na_tabela(arvore->r, table);
        remove_da_arvore_adiciona_na_tabela(arvore->l, table);

        /* guardando no auxiliar e liberando o espaço da arvore */
        auxiliar = arvore->v;
        free(arvore);

        /* adicionando na tabela */
        adicionar(table, novo(auxiliar));
    }

    return;
}


/*************************************************************************************************************
 * DAQUI PARA BAIXO SÃO AS FUNÇÕES ESPECÍFICAS DA ÁRVORE E DA TABELA HASH, COMO INSERIR, BALANCEAR
 * HASH, ETC .. 
 * ***********************************************************************************************************/


void adicionar_na_arvore(Tree **raiz, int v, Tree* pai, Tree** raizOriginal){

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
        adicionar_na_arvore(&((*raiz)-> l),n->v,*raiz,raizOriginal);

    /* caso em que o número adicinado é menor */
    }else{
        adicionar_na_arvore(&((*raiz)-> r),n->v,*raiz,raizOriginal);
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
        printf("Endereço: %p Valor: %d Esquerda: %p Direita: %p Pai: %p \n", x , x->v, x->l, x->r, x->p);
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
            /* printf("\n>> Entrei no balanceamento <<\n\n"); */
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

/* função recursiva para verificar qual o lado mais pesado */

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

                /* printf("\n\n>> Entrei no caso 3 <<\n\n"); */

                /* fazendo a primeira rotação */

                rd(n->r);

                /* atualizando a altura apos a primeira rotação */

                n->r->h = alturaArvore(n->r);
                
                /* fazendo a segunda rotação */

                re(n);
               
                if (n == *RaizOriginal)
                    *RaizOriginal = n->p;

                /* atualizando as alturas */

                n->h =( alturaArvore(n));
            
            /* caso 1 */

            } else {

                /* printf("\n\n>> Entrei no caso 1 <<\n\n"); */

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
                
                /* printf("\n\n>> Entrei no caso 2 <<\n\n"); */

                rd(n);
                if (n == *RaizOriginal)
                    *RaizOriginal = n->p;
                
                n->h =( alturaArvore(n));

            /* caso 4 */
            } else {

                /* printf("\n\n>> Entrei no caso 4 <<\n\n"); */

                /* fazendo a primeira rotação */

                re(n->l);
                
                /* atualizando a altura apos a primeira rotação */

                n->l->h = alturaArvore(n->l);

                /* fazendo a segunda rotação */

                rd(n);
               
                if (n == *RaizOriginal)
                    *RaizOriginal = n->p;

                /* atualizando as alturas */

                n->h =( alturaArvore(n));
         
            }
        }
    }
}


/* função que faz a rotação na esquerda */

void re(Tree* x){
    /* printf("\n\n>> Entrei na rotação da esquerda <<\n\n"); */
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
    /* printf("\n\n!-- Entrei na rotação da direita --!\n\n"); */
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

/* função para liberar arvore */
void tremove(Tree* x){

    if(x != NULL){
        tremove(x->l);
        tremove(x->r);
        free(x);
    }
    return;
}



/********************* FUNÇÕES DA TABELA HASH ***************************/

/* função para criar um novo bloco */
Bloco* novo(int c){

    Bloco* bloco;
    bloco = (Bloco*)malloc(sizeof(Bloco));
    bloco->valor = c;
    bloco->proximo = NULL;
    return bloco;
}

/* função para fazer o hash */
unsigned int hash(int valor, int tam){
	return (valor%tam);
}


/* função para inserir elemento na tabela */

void adicionar(Table *table, Bloco *bloco){

	/* verifica se é necessário atualizar o tamanho */
	if(table->n >= table->tam){
		printf("\n>> Dobrando tamanho <<\n");
		atualizar(table);
	}

	/* verificando a posição onde será inserido */

	unsigned int posicao = hash(bloco->valor, table->tam);

	if(table->b[posicao] == NULL){
		table->b[posicao] = bloco;

	}else{
		bloco->proximo = table->b[posicao];
		table->b[posicao] = bloco;
	}
	
	table->n++;
}

/* funções para liberação */

void tremoveTabela(Table* table){
	int i;
	for(i = 0; i< table->tam; i++){
		tremoveBloco(table->b[i]);
		table->b[i] = NULL;
	}
	table->n = 0;
	
}


void tremoveBloco(Bloco* bloco){
	Bloco *auxiliar;
	while (bloco != NULL){
		auxiliar = bloco->proximo;
		free(bloco);
		bloco = auxiliar;
	}	

}


/* funções para printar arvore */


void exibiTabela(Table *t){
    int i;
    for (i = 0; i < t->tam; i++){
        printf("Chave tabela: %d", i);
        printf(" --> ");
        exibiLista(t->b[i]);
        printf("\n");
    }

    printf("\n\nTamanho: %d, elementos: %d\n\n", t->tam, t->n);
}

void exibiLista(Bloco *x){
    while (x != NULL){
        printf("%d", x->valor);
        printf(" ");
        x = x->proximo;
    }
}

/* função para fazer update no tamanho da tabela */

void atualizar(Table *table){
	int i, tam = table->tam;

	/* criando uma tabela estática auxiliar com o dobro do tamanho */

	Table new;
	new.tam = (tam*2);
	new.b = malloc(sizeof(Bloco *) * new.tam);

	/* prenche os valores da tabela auxiliar como NULL */

	for (i = 0; i < new.tam; i++){
        new.b[i] = NULL;
    }

    /* insere os elementos na nova tabela */
	for (i = 0; i < tam; i++){
    	Bloco *vOrg;
	    vOrg = table->b[i];
	    while (vOrg != NULL){

	    	/* calcula a posição que o valor será inserido */
	        unsigned int posicao = hash(vOrg->valor, new.tam);

	    	/* cria um novo elemento do tipo bloco passando o valor da table original */
	        Bloco *b = novo(vOrg->valor);

	    	/* insere o novo elemento na nova table na posição */
	        if(new.b[posicao] == NULL){
		        new.b[posicao] = b;
	        }else{
				b->proximo = new.b[posicao];
				new.b[posicao] = b;
		    }
            
			vOrg = vOrg->proximo;
			new.n++;
	    }
    }

    /* remove as posições de memoria usadas pela table original */
    tremoveTabela(table);

	/* atribui valores do new na tabela original */
    table->b = new.b;
    table->tam = new.tam;
	table->n = new.n;
}

