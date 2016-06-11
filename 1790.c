#include <stdlib.h>
#include <stdio.h>
#define NMAXVERTICES  50
#define TRUE  1
#define FALSE 0

/**
 * Foi feito o aproveitamento das funcoes contidas no livro do Nivio Ziviani
 * (implementacao : 7.2a7.3e7.8-grafomatriz) na maioria desse codigo
 * e somente foi modificado algumas variaveis para melhor compreensao do codigo
 * por parte do aluno Ronald Pereira
 */


typedef struct TGraph
{
  int Matrix[NMAXVERTICES + 1][NMAXVERTICES + 1];
  int NVertices;
  int NArestas;
} TGraph;

typedef int TPointer;

typedef enum
{
  BRANCO, CINZA, PRETO
}TCor;

void CriaGraph(TGraph *Graph)
{
	short x, y;
	for (x = 0; x <= Graph->NVertices; x++)
	{
		for (y = 0; y <=Graph->NVertices; y++)
		{
			Graph->Matrix[x][y] = 0;
		}
	}
}

void InsereAresta(int *V1, int *V2, TGraph *Graph)
{
	Graph->Matrix[*V1][*V2] = 1;
	Graph->Matrix[*V2][*V1] = 1;
}

char ListaAdjVazia(int *Vertice, TGraph *Graph)
{
	TPointer Aux = 0;
	char ListaVazia = TRUE;

	while (Aux < Graph->NVertices && ListaVazia)
	{
		if (Graph->Matrix[*Vertice][Aux] > 0)
			ListaVazia = FALSE;

	    else
			Aux++;
	}
	return (ListaVazia == TRUE);
}

TPointer PrimeiroListaAdj(int *Vertice, TGraph *Graph)
{
	int Result;
	TPointer Aux = 0;
	char Listavazia = TRUE;

	while (Aux < Graph->NVertices && Listavazia)
	{
		if (Graph->Matrix[*Vertice][Aux] > 0)
		{
			Result = Aux;
			Listavazia = FALSE;
	    }

	    else
			Aux++;
	}
	return Result;
}

void ProxAdj(int *Vertice, TGraph *Graph, int *Adj, TPointer *Prox, short *FimListaAdj)
{
	*Adj = *Prox;
	(*Prox)++;

	while(*Prox < Graph->NVertices && Graph->Matrix[*Vertice][*Prox] == 0)
		(*Prox)++;

	if (*Prox == Graph->NVertices)
		*FimListaAdj = TRUE;
}

void RetiraAresta(int *V1, int *V2, TGraph *Graph)
{

		Graph->Matrix[*V1][*V2] = 0;
		Graph->Matrix[*V2][*V1] = 0;

}

void VisitaDfs(int* count, int u, TGraph *Graph, int* Tempo, int* d, int* t, TCor* Cor, short* Antecessor)
{
	short FimListaAdj;
	TPointer Aux;
	int v;

	Cor[u] = CINZA;
	(*Tempo)++;
	d[u] = (*Tempo);
	(*count)++;

	if (!ListaAdjVazia(&u, Graph))
	{
		Aux = PrimeiroListaAdj(&u, Graph);
		FimListaAdj = FALSE;

		while (!(FimListaAdj))
		{
			ProxAdj(&u, Graph, &v, &Aux, &FimListaAdj);

			if(Cor[v] == BRANCO)
			{
				Antecessor[v] = u;
				VisitaDfs(count, v, Graph, Tempo, d, t, Cor, Antecessor);
			}
		}
	}

	Cor[u] = PRETO;
	(*Tempo)++;
	t[u] = (*Tempo);
}

void DFS(TGraph *Graph, int* count)
{
	int Tempo;
	int d[NMAXVERTICES + 1], t[NMAXVERTICES + 1];
	TCor Cor[NMAXVERTICES + 1];
	short Antecessor[NMAXVERTICES + 1];
	int x;

	Tempo = 0;

	for (x = 0; x < (Graph->NVertices); x++)
	{
		Cor[x] = BRANCO;
	    Antecessor[x] = -1;
	}

	VisitaDfs(count, 0, Graph, &Tempo, d, t, Cor, Antecessor);
}


int main()
{
	int vertices, arestas, origem, destino, x, y;
	int count = 0, aux = 0, valid = 0;
	TGraph Graph;

	while(scanf("%d %d", &vertices, &arestas) != EOF)
	{
		aux = 0;
		Graph.NVertices = vertices;
		Graph.NArestas = 0;

		CriaGraph(&Graph);

		for(x = 0; x < arestas; x++)
		{
			scanf("%d %d", &origem, &destino);
			origem--;
			destino--;

			InsereAresta(&origem, &destino, &Graph);
			Graph.NArestas+=2;
		}

		valid = Graph.NVertices;

		for(x = 0; x < Graph.NVertices; x++)
		{
			if(ListaAdjVazia(&x,&Graph))
				valid--;
		}

		for(x = 0; x < Graph.NVertices; x++)
		{
				for(y = 0; y < Graph.NVertices; y++)
				{
					if(Graph.Matrix[x][y] == 1)
					{
						count = 0;

						RetiraAresta(&x, &y, &Graph);
						DFS(&Graph, &count);

						if(count < valid)
							aux++;

						InsereAresta(&x, &y, &Graph);
					}
				}
		}
		fprintf(stdout, "%d\n", (aux/2));
	}
	return 0;
}
