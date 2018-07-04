#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

/* estruturas */

typedef struct bloco{
      int valor;
      struct bloco *proximo;
}Bloco;

/* struct que simula o vetor */

typedef struct table{
      unsigned int tam;
      unsigned int n;
      struct bloco **b;
}Table;

/* assinaturas das funções */

Bloco* novo(int );
unsigned int hash(int a, int b);
void tremoveTabela(Table* table);
void tremoveBloco(Bloco* bloco);
void update_tam(Table* table);
void adicionar(Table* table , Bloco* bloco );
void exibiLista(Bloco *x);
void exibiTabela(Table *t);
int buscar(Table *table, int valor);
void atualizar(Table *table);
double tvtosec(struct timeval t);

/* função principal */
int main(void){
	srand(time(NULL));
	Table table;
    int valor,i,j,y,k, achou, aleatorio;
    struct timeval a, b;
	double tempo;

	/* alocando a memória necessária para realizar os testes */

    table.b = malloc(sizeof(Bloco*)*(10000));
	table.n = 0;
	table.tam = 10000;

	for(j = 1000; j <= 10000; j+= 10){

		tempo = 0;

		for(k = 0; k < 5000; k++){

			/* preenchendo a tabela com null */
			for(i = 0; i < j; i++){
				table.b[i] = NULL;
			}

			/* adicionando elementos */
			for(y =0; y < j; y++){
				aleatorio = rand() % (j+1);
				adicionar(&table, novo(aleatorio));
			}

			gettimeofday(&b, NULL);
            achou = buscar(&table, rand() % (y+1));
		 	gettimeofday(&a, NULL);

		 	tempo  += tvtosec(a) - tvtosec(b);
			tremoveTabela(&table);
		}

        /* PRINTA O RESULTADO */

		fprintf(stderr, "%d %.20lf\n", j, tempo/5000 );
		printf("%d %.20lf\n", j, tempo/5000 );

	}

}

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
}

void exibiLista(Bloco *x){
    while (x != NULL){
        printf("%d", x->valor);
        printf(" ");
        x = x->proximo;
    }
}

/* função para buscar na árvore */


int buscar(Table *table, int valor){
    int posicao;
    Bloco *bloco;
    posicao = hash(valor, table->tam);
    for (bloco = table->b[posicao]; bloco != NULL; bloco = bloco->proximo){    	
        if(bloco->valor == valor){
            return 1;
        }
    }
    return 0;
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


/* função para converter o tempo */
double tvtosec(struct timeval t){
	return (double) t.tv_sec + t.tv_usec/(double)1e6;

}