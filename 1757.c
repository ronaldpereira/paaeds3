#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define FALSE           0
#define TRUE            1
#define INFINITO        INT_MAX

typedef int TipoValorVertice;

typedef int TipoPeso;

typedef struct TipoGraph
{
	TipoPeso Mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
	int  NumVertices;
	int  NumArestas;
} TipoGraph;

typedef int  TipoApontador;

typedef int  TipoIndice;

typedef struct TipoItem
{
	TipoPeso Chave;
} TipoItem;

typedef TipoItem Vetor[MAXNUMVERTICES + 1];

TipoApontador Aux;

int  i, NArestas;

short  FimListaAdj;

TipoValorVertice V1, V2, Adj;

TipoPeso Peso;

TipoGraph Graph;

TipoValorVertice NVertices;

TipoIndice n;  /*Tamanho do heap*/

TipoValorVertice Raiz;

void FGVazio(TipoGraph *Graph)
{
	int  i, j;
	for (i = 0; i <= Graph->NumVertices; i++)
	{
		for (j = 0; j <= Graph->NumVertices; j++)
			Graph->Mat[i][j] = 1;
    }
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoPeso *Peso, TipoGraph *Graph)
{
	Graph->Mat[*V1][*V2] = *Peso;
}

short  ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGraph *Graph)
{
	return (Graph->Mat[Vertice1][Vertice2] > 0);
}

/*-- Operadores para obter a lista de adjacentes --*/
short  ListaAdjVazia(TipoValorVertice *Vertice, TipoGraph *Graph)
{
	TipoApontador Aux = 0;
	short ListaVazia = TRUE;
	while (Aux < Graph->NumVertices && ListaVazia)
	{
	if (Graph->Mat[*Vertice][Aux] > 0)
    	ListaVazia = FALSE;
    else
		Aux++;
	}

	return (ListaVazia == TRUE);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGraph *Graph)
{
	TipoValorVertice Result;
	TipoApontador Aux = 0;
	short Listavazia = TRUE;

	while (Aux < Graph->NumVertices && Listavazia)
	{
		if (Graph->Mat[*Vertice][Aux] > 0)
		{
			Result = Aux;
			Listavazia = FALSE;
		}
		else
			Aux++;
	}

	return Result;
}


void ProxAdj(TipoValorVertice *Vertice, TipoGraph *Graph, TipoValorVertice *Adj, TipoPeso *Peso, TipoApontador *Prox, short *FimListaAdj)
{
/* --Retorna Adj apontado por Prox--*/
	*Adj = *Prox;
	*Peso = Graph->Mat[*Vertice][*Prox];
	(*Prox)++;
	while (*Prox < Graph->NumVertices && Graph->Mat[*Vertice][*Prox] == 0)
		(*Prox)++;

	if (*Prox == Graph->NumVertices)
		*FimListaAdj = TRUE;
}

/* Local variables for AgmPrim: */
struct LOC_AgmPrim
{
  TipoPeso P[MAXNUMVERTICES + 1];
  TipoValorVertice Pos[MAXNUMVERTICES + 1];
};

void RefazInd(TipoIndice Esq, TipoIndice Dir, TipoItem *A, TipoPeso *P, TipoValorVertice *Pos)
{
	TipoIndice i = Esq;
	int j = i * 2;
	TipoItem x;
	x = A[i];

	while (j <= Dir)
	{
		if (j < Dir)
		{
			if (P[A[j].Chave] > P[A[j+1].Chave])
				j++;
		}

		if (P[x.Chave] <= P[A[j].Chave])
			break; // Aqui jaz um goto

		A[i] = A[j];
		Pos[A[j].Chave] = i;
		i = j;
		j = i * 2;
	}

	A[i] = x;
	Pos[x.Chave] = i;
}

void Constroi(TipoItem *A, TipoPeso *P, TipoValorVertice *Pos)
{
	TipoIndice Esq;
	Esq = n / 2 + 1;

	while (Esq > 1)
	{
		Esq--;
		RefazInd(Esq, n, A, P, Pos);
	}
}

TipoItem RetiraMinInd(TipoItem *A, TipoPeso *P, TipoValorVertice *Pos)
{
	TipoItem Result;

	if (n < 1)
	{
		return Result;
	}

		Result = A[1]; A[1] = A[n];
		Pos[A[n].Chave] = 1; n--;
		RefazInd(1, n, A, P, Pos );
		return Result;
}

void DiminuiChaveInd(TipoIndice i, TipoPeso ChaveNova, TipoItem *A, TipoPeso *P, TipoValorVertice *Pos)
{
	TipoItem x;

	if (ChaveNova > P[A[i].Chave])
	{
		return;
	}

	P[A[i].Chave] = ChaveNova;

	while (i > 1 && P[A[i / 2].Chave] > P[A[i].Chave])
	{
		x = A[i / 2]; A[i / 2] = A[i];
		Pos[A[i].Chave] = i / 2; A[i] = x;
		Pos[x.Chave] = i; i /= 2;
    }
}

int AgmPrim(TipoGraph *Graph, TipoValorVertice *Raiz, int count)
{
	int  Antecessor[MAXNUMVERTICES + 1];
	short  Itensheap[MAXNUMVERTICES + 1];
	Vetor A;
	TipoPeso P[MAXNUMVERTICES + 1];
	TipoValorVertice Pos[MAXNUMVERTICES + 1];
	TipoValorVertice u, v;
	TipoItem TEMP;

	for (u = 0; u <= Graph->NumVertices; u++)
	{
		/*Constroi o heap com todos os valores igual a INFINITO*/
		Antecessor[u] = -1;
		P[u] = INFINITO;
		A[u+1].Chave = u;   /*Heap a ser construido*/
		Itensheap[u] = TRUE;
		Pos[u] = u + 1;
	}

	n = Graph->NumVertices; P[*Raiz] = 0;
	Constroi(A, P, Pos);

	while (n >= 1)  /*enquanto heap nao vazio*/
	{
		TEMP = RetiraMinInd(A, P, Pos);
		u = TEMP.Chave;
		Itensheap[u] = FALSE;

		if (u != *Raiz)
		{
			if(Graph->Mat[u][(Antecessor[u])] == 2)
				count++;
		}

		if (!ListaAdjVazia(&u, Graph))
		{
			Aux = PrimeiroListaAdj(&u, Graph);
     		FimListaAdj = FALSE;

	     	while (!FimListaAdj)
		 	{
				ProxAdj(&u, Graph, &v, &Peso, &Aux, &FimListaAdj);
	    		if (Itensheap[v] && Peso < P[v])
				{
					Antecessor[v] = u;
					DiminuiChaveInd(Pos[v], Peso, A, P, Pos);
	        	}
			}
		}
	}
	return count;
}

int main()
{
	int i, j, t, count;

	scanf("%d", &t);

	for(i = 0; i < t; i++)
	{
		count = 0;
		scanf("%d %d", &NVertices, &NArestas);
		Graph.NumVertices = NVertices;
		Graph.NumArestas = 0;
		FGVazio(&Graph);

		for(j = 0; j < NArestas; j++)
		{
			scanf("%d %d", &V1, &V2);
			Graph.NumArestas++;
			Peso = 2;
			InsereAresta(&V1, &V2, &Peso, &Graph);
			InsereAresta(&V2, &V1, &Peso, &Graph);
		}

		Raiz = 0;
		printf("%d\n", AgmPrim(&Graph, &Raiz, count));
	}
	return 0;
}
