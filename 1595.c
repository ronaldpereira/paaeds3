#include <stdio.h>
#include <stdlib.h>

int compare(const void *arg1, const void *arg2)
{
	int a = *(const int*)arg1;
	int b = *(const int*)arg2;

	if (a < b)
		return -1;
	else if (a > b)
		return 1;
	else
		return 0;
}

int main()
{
	int testes;
	int s, c, r;
	double tempo;
	int *v;
	int i, j;

	scanf("%d", &testes);

	for(i = 0; i < testes; i++)
	{
		scanf("%d %d %d", &s, &c, &r);

		v = (int*) calloc(s,sizeof(int));

		for(j = 0; j < s; j++)
			scanf("%d", &v[j]);

		qsort(v, s, sizeof(int), compare);

		tempo = 0;

		for(j = 0; j < s ; j++)
		{
			if(j < c)
				tempo += (double)1/(v[j]+r);

			else
				tempo += (double)1/v[j];
		}

		printf("%.2lf\n", tempo);

		free(v);
	}

	return 0;
}
