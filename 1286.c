#include <stdio.h>
#include <stdlib.h>

int knapsack(int n, int p, int *t, int *pn)
{
	if(n < 0)
		return 0;

	if(p < pn[n])
		return knapsack(n-1, p, t, pn);

	if((knapsack(n-1, p-pn[n], t, pn)+t[n]) > knapsack(n-1, p, t, pn))
		return knapsack(n-1, p-pn[n], t, pn)+t[n];

	else
		return knapsack(n-1, p, t, pn);
}

int main()
{
	int n, p;
	int t[20], pn[20];
	int i;

	while(scanf("%d", &n) && n!= 0)
	{
		scanf("%d", &p);

		for(i = 0; i < n; i++)
			scanf("%d %d", &t[i], &pn[i]);

		printf("%d min.\n", knapsack(n-1, p, t, pn));
	}
	return 0;
}
