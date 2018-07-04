#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*********************************************************************
********************* GRAFO - LISTA DE ADJACÊNCIA ********************
*********************************************************************/

typedef struct bloco{
    int valor;
    struct bloco *proximo;
}Bloco;

typedef struct table{
    struct bloco **b;
}Table;


/* chamadas das funções */

int quantidade_arestas();
void adicionar(Table *table, int ,int *vetor);
Bloco* novo(int c);
void exibiTabela(Table *t, int tam, int *vetor);
void exibiLista(Bloco *x);
void preencher_vetor(int *vetor, int arestas);
int verifica_posicao_chave(int *vetor, int valor, int arestas);
int busca_ligacao(Table *table, int valor, int posicao_chave);

/* função principal */

int main (void){

    Table table;

    /* verificando a quantidade de arestas (elementos) no grafo para alocar memória/criar vetor auxiliar*/
    int arestas = quantidade_arestas();

    /* iniciando a tabela e o vetor auxiliar de posições */
    table.b = malloc(sizeof(Bloco*)*(arestas));
    int vetor_posicoes[arestas];
    
	/* preenchendo a tabela com null */
	for(int i = 0; i < arestas; i++){
		table.b[i] = NULL;
	}

    /* preenchendo o vetor com as arestas */
    preencher_vetor(vetor_posicoes, arestas);

    /* adicinando as ligações (vértices) na tabela */
    adicionar(&table, arestas, vetor_posicoes);

    /* exibindo */
    exibiTabela(&table, arestas, vetor_posicoes);

    return 0;
}


int quantidade_arestas(){

    /* abrindo o arquivo */
    
    FILE *arq;
    arq = fopen("grafo.txt", "r");
    char linha[100], *resultado;
    int contador = 0;

    while(!feof(arq)){
        resultado = fgets(linha, 100, arq);
        if(strcmp (linha, "#\n") == 0) break;
        else contador++;
    }

    fclose(arq);
    return contador;
}


void preencher_vetor(int *vetor, int arestas){

    FILE *arq;
    arq = fopen("grafo.txt", "r");
    char linha[100], *resultado;
    int contador = 0;

    while(contador < arestas){
        resultado = fgets(linha, 100, arq);
        vetor[contador] = atoi(linha);
        contador++;
    }

    fclose(arq);
}


void adicionar (Table *table, int arestas , int *vetor){
    
    FILE *arq;
    arq = fopen("grafo.txt", "r");
    char linha[100], *resultado, *split;
    int  contador = 0, contador_linha = 0, chave, valor, posicao_chave;

    while(!feof(arq)){

        resultado = fgets(linha, 100, arq);

        /* começa ler após o # (separador) */
        if(contador > arestas){
            
            /* quebrando os dois elementos da linha */
            contador_linha = 0;
            split = strtok(linha, " ");

            /* laço para guardar os dois elementos da linha */
            while (split != NULL){

                if(contador_linha == 0){
                    /* pegando o primeiro elemento da linha (primeira vez que o while roda) */
                    chave = atoi(split);
                }else{
                    /* pegando o segundo elemento da linha (segunda vez que o while roda) */
                    valor = atoi(split);
                }
                contador_linha++;
                split = strtok (NULL, " ");
            }

            /* verificando a posição correspondente da chave no vetor auxiliar */
            posicao_chave = verifica_posicao_chave(vetor, chave , arestas);

            /* verifica se já não existe essa ligação */
            if(busca_ligacao(table, valor, posicao_chave ) == 0){

                /* criando um novo bloco e adicionando na chave correspondente */
                Bloco *bloco = novo(valor);
                
                if(table->b[posicao_chave] == NULL){
                    table->b[posicao_chave] = bloco;
                }else{
                    bloco->proximo = table->b[posicao_chave];
                    table->b[posicao_chave] = bloco;
                }


                /* se a lista não for direcionada, pode usar esse trecho de código 

                posicao_chave = verifica_posicao_chave(vetor, valor, arestas);
                Bloco *bloco2 = novo(chave);

                if(table->b[posicao_chave] == NULL){
                    table->b[posicao_chave] = bloco2;
                }else{
                    bloco2->proximo = table->b[posicao_chave];
                    table->b[posicao_chave] = bloco2;
                }

                */
            }
        }

        contador++;
    }

    fclose(arq);
}

/* função para criar um novo bloco */
Bloco* novo(int c){

    Bloco* bloco;
    bloco = (Bloco*)malloc(sizeof(Bloco));
    bloco->valor = c;
    bloco->proximo = NULL;
    return bloco;
}


void exibiTabela(Table *t, int tam, int *vetor){
    int i;
    for (i = 0; i < tam; i++){
        printf("[%d]", vetor[i]);
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

int verifica_posicao_chave(int *vetor, int valor, int arestas) {
    int i;
    for(i = 0; i < arestas; i++){
        if(vetor[i] == valor){
            return i;
        }
    }
}

int busca_ligacao(Table *table, int valor, int posicao_chave){

    Bloco *bloco = table->b[posicao_chave];

    while(bloco != NULL){        
        if(bloco->valor == valor) return 1;
        bloco = bloco->proximo;
    }

    return 0;
}