#include <stdio.h>
#include <stdlib.h>

void imprimegrafo(int **graph, int cidade)
{
	int i, j;

	for(i = 1; i <= cidade; i++)
	{
		for(j = 1; j <= cidade; j++)
		{
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void DFS(int **graph, int cidade, int vertices, int x, int iant, int jant)
{
	int i, j;

	for(i = x; i <= cidade; i++)
	{
		for(j = 1; j <= cidade; j++);
		if(graph[i][j] == 1 && i != jant)
		{
			iant = i;
			jant = j;
			printf("aresta %d --> %d\n", iant, jant);
			printf("entrou %d --> %d\n", i, j);
			DFS(graph, cidade, vertices++, j, iant, jant);
		}
	}
}

void inicializaDFS(int **graph, int cidade)
{
	int aux = 0;
	int i, j;
	int vertices;

	for(i = 1; i <= cidade; i++)
	{
		for(j = 1; j <= cidade; j++)
		{
			if(graph[i][j] == 1 && i < j)
			{
				graph[i][j] = 0;
				graph[j][i] = 0;
				vertices = 0;
				DFS(graph, cidade, vertices, 1, 0, 0);
				graph[i][j] = 1;
				graph[j][i] = 1;
				if(vertices < cidade)
					aux++;
			}
		}
	}
	printf("%d\n", aux);
}

int main()
{
	int cidade, ponte;

	while(1)
	{
		scanf("%d %d", &cidade, &ponte);

		if(cidade == 0)
			break;

		int **graph;
		int i;

		graph = (int**) calloc(cidade+1,sizeof(int));
		for(i = 0; i <= cidade+1; i++)
		{
			graph[i] = (int*) calloc(cidade+1,sizeof(int));
		}

		int x, y;

		for(i = 0; i < ponte; i++)
		{
			scanf("%d %d", &x, &y);

				graph[x][y] = 1;
				graph[y][x] = 1;
		}
		inicializaDFS(graph, cidade);
	}

	return 0;
}
