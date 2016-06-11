#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int *entrada, *retirados, *restantesfila, *restantespilha;
	int n, i, l, error;
	int opcao, num;

	while(scanf("%d", &n) != EOF)
	{
		int pilha = 1;
		int fila = 1;
		int filapriori = 1;
		int maior = 0;
		int error = 0, err = 0;
		int e = 0;
		int r = 0;
		int p;

		entrada = (int*) calloc(1010,sizeof(int));
		retirados = (int*) calloc(1010,sizeof(int));
		restantesfila = (int*) calloc(1010,sizeof(int));
		restantespilha = (int*) calloc(1010,sizeof(int));

		for(i = 0; i < n; i++)
		{
			scanf("%d %d", &opcao, &num);

			if(opcao == 1)
			{
				entrada[e] = num;
				restantesfila[e] = num;
				restantespilha[e] = num;
				e++;
				p = 0;

				if(num > maior)
					maior = num;
			}

			else if(opcao == 2)
			{
				for(l = 0; l < e; l++)
				{
					if(restantesfila[l] == num)
					{
						err = 0;
						break;
					}

					else
						err = 1;
				}

				if(restantesfila[r] != num)
					fila = 0;

				retirados[r] = num;
				r++;

				for(l = 0; l < e; l++)
				{
					if(restantesfila[l] == num)
					{
						restantesfila[l] = 0;
						break;
					}
				}

				if(p > 0)
				{
					while(restantespilha[e-p-1] == 0)
						p++;
				}

				else
				{
				if(restantespilha[e-p-1] != num)
					pilha = 0;
				}

				for(l = 0; l < e; l++)
				{
					if(restantespilha[e-l] == num)
					{
						restantespilha[e-l] = 0;
						break;
					}
				}

				if(err == 1) // Saída = impossible (tenta retirar uma posicao que nao foi inserida)
					error = 1;

				if(maior != num)
					filapriori = 0;

				else
				{
					maior = 0;

					for(l = 0; l < e; l++)
					{
						if(restantesfila[l] > maior)
							maior = restantesfila[l];
					}
				}

				p++;
			}
		}

		// Impressões das saídas
		if(error == 1)
			printf("impossible\n");

		else if(filapriori == 1 && fila == 0 && pilha == 0)
			printf("priority queue\n");

		else if(fila == 1 && filapriori == 0 && pilha == 0)
			printf("queue\n");

		else if(pilha == 1 && filapriori == 0 && fila == 0)
			printf("stack\n");

		else if((filapriori == 1 && fila == 1) || (filapriori == 1 && pilha == 1) || (fila == 1 && pilha == 1))
			printf("not sure\n");

		else
			printf("impossible\n");

		free(entrada);
		free(retirados);
		free(restantesfila);
		free(restantespilha);
	}
	return 0;
}
