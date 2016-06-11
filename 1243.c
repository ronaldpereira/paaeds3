#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contaString(char *c)
{
    unsigned int i, aux = 0;
    //Tabela ASCII --> A = 65 e Z = 90, a = 97 e z = 122
    for(i = 0; i < strlen(c); i++)
    {
        if(!(((int)c[i] >= 65 && (int)c[i] <= 90) || ((int)c[i] >= 97 && (int)c[i] <= 122)))
            aux++;
    }
    if(aux == 0 && strlen(c) >= 1)
        return (strlen(c));
    else if(aux == 1 && c[strlen(c)-1] == '.' && strlen(c) > 1)
        return (strlen(c)-1);
    else
        return 0;
}

int main()
{
    int num = 0, den = 0, aux, result;
    char *c, *tok;

    c = (char*) malloc(1000*sizeof(char));

    while(fgets(c, 1000, stdin) != NULL)
    {
            if(strlen(c) == 2)
                tok = strtok(c, "\n");
            else
                tok = strtok(c, " \n");
            aux = contaString(tok);
            num += aux;
            if(aux > 0)
                den++;
            while(tok != NULL)
            {
                tok = strtok(NULL, " \n");
                if(tok != NULL)
                {
                    aux = contaString(tok);
                    num += aux;
                    if(aux > 0)
                        den++;
                }
            }
                if(tok == NULL)
                {
                    if(den == 0)
                        den = 1;
                    result = num/den;
                    if(result <= 3)
                        printf("250\n");
                    else if(result == 4 || result == 5)
                        printf("500\n");
                    else
                        printf("1000\n");
                    den = 0;
                    num = 0;
                }
    }
    free(c);

    return 0;
}
