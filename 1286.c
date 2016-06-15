#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, p;
	int i, j;

	while(scanf("%d", &n) && n!= 0)
	{
		scanf("%d", &p);

		int *tempo, *peso, **tabela;

		tempo = (int*) calloc(n+1,sizeof(int));
		peso = (int*) calloc(n+1,sizeof(int));

		tabela = (int**) calloc(n+1,sizeof(int*));
		for(i = 0; i <= n; i++)
			tabela[i] = (int*) calloc(p+1,sizeof(int*));

		for(i = 1; i <= n; i++)
			scanf("%d %d", &tempo[i], &peso[i]);

		for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= p; j++)
			{
				if(peso[i] <= j)
				{
					tabela[i][j] = tempo[i] + tabela[i-1][j-peso[i]];

					if(tabela[i-1][j] > tabela[i][j])
						tabela[i][j] = tabela[i-1][j];
				}

				else
					tabela[i][j] = tabela[i-1][j];
			}
		}

		printf("%d min.\n", tabela[n][p]);
	}
	return 0;
}
