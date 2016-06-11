#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fazLeituraEAloca(int **hash, int mod, int n)
{
	int i, j, num;

	for(i = 0; i < n; i++)
	{
		scanf("%d", &num);

		for(j = 0; j < n; j++)
		{
			if(hash[num%mod][j] == 0)
			{
				hash[num%mod][j] = num;
				break;
			}
		}
	}
}

void imprimeHash(int **hash, int mod)
{
	int i, j;

	for(i = 0; i < mod; i++)
	{
		printf("%d -> ", i);
		for(j = 0; ; j++)
		{
			if(hash[i][j] == 0)
			{
				printf("\\\n");
				break;
			}
			else
				printf("%d -> ", hash[i][j]);
		}
	}
}

int main()
{
	int n, m, c;
	int i, j;
	int **hash;

	scanf("%d", &n);

	for(i = 0; i < n; i++)
	{
		scanf("%d %d", &m, &c);

		hash = (int**) calloc(m+1, sizeof(int*));
		for(j = 0; j <= m; j++)
			hash[j] = (int*) calloc(c+1, sizeof(int));

		fazLeituraEAloca(hash, m, c);

		imprimeHash(hash, m);

		if(i < n-1)
			printf("\n");

		for(j = 0; j <= m; j++)
			free(hash[j]);
		free(hash);

	}

	return 0;
}
