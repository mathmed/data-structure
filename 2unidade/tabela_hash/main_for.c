	srand(time(NULL));
	Table table;
    int valor,i,j,y,k, achou, aleatorio;
    struct timeval a, b;
	double tempo;

    table.b = malloc(sizeof(Bloco*)*(1000));
	table.n = 0;
	table.tam = 1000;



	for(j = 1000; j <= 10000; j+= 500){

		tempo = 0;


			/* preenchendo a tabela com null */
			for(i = 0; i < j; i++){
				table.b[i] = NULL;
			}

			for(y =0; y < j; y++){
				aleatorio = rand() % (j+1);
				adicionar(&table, novo(aleatorio));
			}

			gettimeofday(&b, NULL);
            achou = buscar(&table, rand() % (y+1));
		 	gettimeofday(&a, NULL);

		 	tempo  += tvtosec(a) - tvtosec(b);
			tremoveTabela(&table);
		

        /* PRINTA O RESULTADO */

		fprintf(stderr, "%d %.20lf\n", j, tempo/100000 );
		printf("%d %.20lf\n", j, tempo/100000 );

	}