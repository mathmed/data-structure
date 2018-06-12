#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>


/* estruturas */

typedef struct bloco{
      int vl;
      struct bloco *e;
}Bloco;

typedef struct table{
      unsigned int tam;
      unsigned int n;
      unsigned int col;
      struct bloco **v;
}Table;

/* assinaturas das funções */

Bloco* novo(int );
unsigned int hash(int , int );
void remove(Bloco* bloco );
void update_tam(Table* );
void insercao(Table* , Bloco* );
void printar(Bloco* );
Bloco * busca(Table* ,int );


Bloco* novo(int c){

    Bloco* bloco;
    bloco = (Bloco*)malloc(sizeof(Bloco));
    bloco->vl = c;
    bloco->e = NULL;
    return bloco;
}

unsigned int hash(int vl, int tam)
{
	return vl%tam;
}

void remove(Bloco* bloco)
{
	while (bloco != NULL)
	{
		Bloco *aux = bloco->e;
		free(bloco);
		bloco = aux;
	}
}

void update_tam(Table *table)
{
        //Dobra o tamanho da table
	int i, tam = table->tam;
	Table new;
	new.tam = (tam*2);
	new.v = malloc(sizeof(Bloco *) * new.tam);
	// prenche os valores table aux como NULL
	for (i = 0; i < new.tam; i++)
    	{
             new.v[i] = NULL;
    	}
    	// insere os elementos na nova table com o valor dobrado
	for (i = 0; i < tam; i++)
    	{
    	     Bloco *vOrg;
	     vOrg = table->v[i];
	     while (vOrg != NULL)	     {
	     // calcula a posição que o valor será inserido na nova table através da função hash
	           unsigned int posicao = hash(vOrg->vl, new.tam);
	     // cria um novo elemento do tipo lista passando o valor da table original
	           Bloco *b = novo(vOrg->vl);
	     // insere o novo elemento na nova table na posição retornada pela função rash
	           if(new.v[posicao] == NULL){
		        new.v[posicao] = b;
	           }
		   else{
			b->e = new.v[posicao];
			new.v[posicao] = b;
		   }
		   vOrg = vOrg->e;
	      }
         }
         // remove as posições de memoria usadas pela table original
         for (i = 0; i < table->tam; i++){
             remove((table->v[i]));
    	 }
   	 free(table->v);
         table->v = new.v;
         table->tam = new.tam;
}

void insercao(Table *table, Bloco *bloco)
{
	
	if(table->n >= table->tam){
		update_tam(table);
	}
	unsigned int posicao = hash(bloco->vl, table->tam);
	if(table->v[posicao] == NULL)
	{
		table->v[posicao] = bloco;
	}
	else
	{
		bloco->e = table->v[posicao];
		table->v[posicao] = bloco;
	}
	table->n++;
}

void printar(Bloco *bloco)
{
    while (bloco != NULL)
    {
        printf(" %d", bloco->vl);
        printf(" ");
        bloco = bloco->e;
    }
}


Bloco * busca(Table *table, int valor)
{
    int posicao;
    Bloco *bloco;
    posicao = hash(valor, table->tam);
    for (bloco = table->v[posicao]; bloco != NULL; bloco = bloco->e)
    {    	
        if(bloco->vl == valor)
        {
            break;
        }
    }
    return bloco;
}

int main()
{
    Table table;
    double m;
    int n = 100;
    int s = 100;
    int valor;
    int i,j,y;
    srand(time(NULL));

    struct timeval a, b;

    do
    {

    table.v = malloc(sizeof(Bloco *)*(100));
	table.n = 0;
	table.tam = 100;
        m = 0;

	for(i = 0; i < 100; i++)
	{
	     table.v[i] = NULL;
	}

 	for (i = 0; i < n; i++)
	{
	     unsigned int num;
	     num = rand()% (n+500);
	     insercao(&table, novo(num));
	}
	for(j = 0; j < s; j++){
	    y = rand() %(n+500);
	    gettimeofday(&b, NULL);
	    busca(&table, y);
	    gettimeofday(&a, NULL); 
	    
	    m = m + a.tv_sec - b.tv_sec + 1e-6 * (a.tv_usec - b.tv_usec);
            
	 }

	 for (i = 0; i < n; i++)
	 {
	    remove((table.v[i]));
	 }
	 free(table.v);        
	 printf("%d ", n);	
         m = m / s;	
	 printf("%.8f\n" , m);
         n = n + 100;
    }while(n<=100000);

    return 0;
}  

