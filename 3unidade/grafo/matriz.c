#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*********************************************************************
********************* GRAFO - MATRIZ DE ADJACÊNCIA ********************
*********************************************************************/


/* chamadas das funções */

int quantidade_arestas();
void preencher_vetor(int *vetor, int arestas);
void adicionar ( int arestas , int *vetor, int matriz[arestas][arestas]);
int verifica_posicao_chave(int *vetor, int valor, int arestas) ;
void exibir(int arestas, int *vetor, int matriz[arestas][arestas]);

/* função principal */

int main (void){

    int i, j, arestas;

    /* verificando a quantidade de arestas (elementos) */

    arestas = quantidade_arestas();

    /* iniciando a matriz e o vetor auxiliar de posições */

    int matriz[arestas][arestas];
    int vetor_posicoes[arestas];
    
	/* preenchendo a matriz com 0 */
	for(i = 0; i < arestas; i++)
		for(j = 0; j < arestas; j++)
            matriz[i][j] = 0;

    /* preenchendo o vetor com os elementos */
    preencher_vetor(vetor_posicoes, arestas);

    /* adicinando as ligações */
    adicionar(arestas, vetor_posicoes, matriz);

    /* exibindo matriz */

    exibir(arestas, vetor_posicoes, matriz);

    return 0;
}


int quantidade_arestas(){
    
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
    /* abrindo o arquivo */
    
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


void adicionar (int arestas , int *vetor, int matriz[arestas][arestas]){
    
    FILE *arq;
    arq = fopen("grafo.txt", "r");
    char linha[100], *resultado, *split;
    int  contador = 0, contador_linha = 0, chave, valor, posicao_chave, posicao_valor;

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

            /* verificando a posição correspondente da chave */
            posicao_chave = verifica_posicao_chave(vetor, chave , arestas);
            posicao_valor = verifica_posicao_chave(vetor, valor , arestas);

            /* orientada (deixar somente essa linha) */
            matriz[posicao_chave][posicao_valor] = 1;

            /* não orientada (deixar a de cima e essa também) */
            //matriz[posicao_valor][posicao_chave] = 1;

        }

        contador++;
    }

    fclose(arq);
}

int verifica_posicao_chave(int *vetor, int valor, int arestas) {
    int i;
    for(i = 0; i < arestas; i++){
        if(vetor[i] == valor){
            return i;
        }
    }
}


void exibir(int arestas, int *vetor, int matriz[arestas][arestas]){

    int i, j, k;

    printf("     ");
    for(k=0; k < arestas; k++) printf("[%d] ", vetor[k]);
    printf("\n");

    for(i = 0; i < arestas; i++){
        printf("[%d]", vetor[i]);
        for(j = 0; j < arestas; j++){
            printf("   %d ", matriz[i][j]);
        }
    
        printf("\n");
    }   
}