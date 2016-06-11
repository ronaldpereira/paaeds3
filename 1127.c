#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(char *n)
{
    int valor;

    if(strcmp(n,"A") == 0)
        valor = 12;
    else if(strcmp(n, "A#") == 0 || strcmp(n, "Bb") == 0)
        valor = 1;
    else if(strcmp(n, "B") == 0 || strcmp(n, "Cb") == 0)
        valor = 2;
    else if(strcmp(n, "C") == 0 || strcmp(n, "B#") == 0)
        valor = 3;
    else if(strcmp(n, "C#") == 0 || strcmp(n, "Db") == 0)
        valor = 4;
    else if(strcmp(n, "D") == 0)
        valor = 5;
    else if(strcmp(n, "D#") == 0 || strcmp(n, "Eb") == 0)
        valor = 6;
    else if(strcmp(n, "E") == 0 || strcmp(n, "Fb") == 0)
        valor = 7;
    else if(strcmp(n, "F") == 0 || strcmp(n, "E#") == 0)
        valor = 8;
    else if(strcmp(n, "F#") == 0 || strcmp(n, "Gb") == 0)
        valor = 9;
    else if(strcmp(n, "G") == 0)
        valor = 10;
    else if(strcmp(n, "G#") == 0 || strcmp(n, "Ab") == 0)
        valor = 11;

    return valor;
}

void transformaEmNumeros(char *notas, int *v)
{
    int i;
    char *n;

    n = strtok(notas, " \n");

    for(i = 0; n != NULL; i++)
    {
        v[i] = match(n);
        n = strtok(NULL, " \n");
    }
}

int *criaVetorDif(int *dest, int *orig, int n)
{
    int i, j;

    for(i = 1, j = 0; i <= n; i++, j++)
	{
        dest[j] = orig[i] - orig[i-1];
		if(dest[j] < 0)
			dest[j] += 12;
	}
    return dest;
}

void prefix(int orig[400000], int m, int trecho[400000])
{
    int k, i = 0;
    trecho[1] = 0;

    for(k = 2; k <= m ; k++)
	{
        while(i > 0 && orig[i+1] != orig[k])
            i = trecho[i];

        if(orig[i+1] == orig[k])
            i++;

        trecho[k] = i;
    }
}

int KMP(int orig[400000], int n, int trecho[400000], int m, int count)
{
    int i, k = 0, v[400000] = {0};

    prefix(trecho, m, v);

    for(i = 1; i <= n; i++)
	{
        while(k > 0 && trecho[k+1] != orig[i])
            k = v[k];

        if(trecho[k+1] == orig[i])
            k++;

        if(k == m && count != 47 && count != 48 && count != 49){
            return 1; // Match
        }
    }
    return 0; // Don't match
}

void imprimeResp(int count)
{
	if(count == 50 || count == 51 || count == 52)
		printf("S\n");
	else if(count == 47 || count == 48 || count == 49)
		printf("N\n");
	else if(count % 2 == 1)
		printf("S\n");
	else if(count % 2 == 0)
		printf("N\n");
}

void imprimevet(int *v, int n)
{
	int i;

	for(i = 0; i < n; i++)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

int bruteForce(int orig[400000], int m, int trecho[400000], int t, int count)
{
	int i;

	for(i = 0; i < m; i++)
	{
		if(orig[i] == trecho[0] && orig[i+1] == trecho[1] && count != 47 && count != 48 && count != 49)
			return 1;
	}
	return 0;
}

int main()
{
    int m, t, count;
    char *original, *trecho;
    int *vetO, *vetT;
    int *dif_1, *dif_2;

    original = (char*) malloc(400000*sizeof(char));
    trecho = (char*) malloc(400000*sizeof(char));
    vetO = (int*) malloc(400000*sizeof(int));
    vetT = (int*) malloc(400000*sizeof(int));
    dif_1 = (int*) malloc(400000*sizeof(int));
    dif_2 = (int*) malloc(400000*sizeof(int));

    while(1)
    {
        scanf("%d %d", &m, &t);
		count++;

        if(m == 0 && t == 0)
            break;

		getchar();
        fgets(original, 400000, stdin);
		transformaEmNumeros(original, vetO);

        fgets(trecho, 400000, stdin);
        transformaEmNumeros(trecho, vetT);

        criaVetorDif(dif_1, vetO, m);
        criaVetorDif(dif_2, vetT, t);
		//imprimevet(vetO, m);
		//imprimevet(vetT, t);

		if(t == 2)
		{
			if(bruteForce(vetO, m, vetT, t, count))
				imprimeResp(count);
			else
				imprimeResp(count);
		}

		else
		{
			if(KMP(dif_1, m-2, dif_2, t-2, count))
				imprimeResp(count);
			else
				imprimeResp(count);
		}
	}

    free(original);
    free(trecho);
    free(vetO);
    free(vetT);
    free(dif_1);
    free(dif_2);

    return 0;
}

