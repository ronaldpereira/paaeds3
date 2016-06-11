#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 256

int BMH(char *orig, long n, char *trecho, long m)
{
    long i, j, k, d[MAXCHAR+1];

    for (j = 0; j <= MAXCHAR ; j++)
        d[j] = m;

    for (j = 1; j < m; j++)
        d[trecho[j-1]] = m - j;

    i = m;

    while (i <= n)
    {
        k = i ;
        j = m;

        while(orig[k-1] == trecho[j-1] && j > 0)
        {
            k--;
            j--;
        }

        if (j == 0)
            return k; // Returns the matching position

        i += d[orig[i-1]];
    }
    return -1; // False
}

void retiradotexto(int pos, char *texto, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		texto[pos+i] = 'x';
	}
}

int main()
{
    int i, j, k, pos, cont;
    int n, m;
    char *emoticon, *texto, proib[100][15], conv[100][81];

    emoticon = (char*) malloc(100*sizeof(char));
    texto = (char*) malloc(100*sizeof(char));

    while(1)
    {
        scanf("%d %d\n", &n, &m);

		cont = 0;

        if(n == 0 && m == 0)
            break;

        for(i = 0; i < n; i++)
        {
            fgets(emoticon, 15, stdin);
            strcpy(proib[i], emoticon);
        }

        for(i = 0; i < m; i++)
        {
            fgets(texto, 100, stdin);
            strcpy(conv[i], texto);
        }

		for(k = 0; k <= 10; k++)
		{
	        for(i = 0; i < n; i++)
	        {
	            for(j = 0; j < m; j++)
	            {
				printf("%s\n", conv[j]);
					pos = 0;
					while(pos != -1)
					{
						pos = BMH(conv[j], strlen(conv[j])-1, proib[i], strlen(proib[i])-1);
						if(pos != -1)
						{
							retiradotexto(pos, conv[j], strlen(proib[i])-1);
							cont++;
						}
					}
	            }
	        }
		}

		printf("%d\n", cont);
    }

    free(emoticon);
    free(texto);
    return 0;
}
