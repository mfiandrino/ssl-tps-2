#include "histograma.h"

int *implementarHistograma(char *implementacion)
{
    if(strcmp(implementacion,"1") == 0)
        return histograma1();

    else if(strcmp(implementacion,"2") == 0)
        return histograma2();

    else if(strcmp(implementacion,"3") == 0)
        return histograma3();
        
    else
        return histograma4();
}

int validarHistograma(char *implementacion)
{
    if(strcmp(implementacion,"1") == 0 || strcmp(implementacion,"2") == 0 || strcmp(implementacion,"3") == 0 || strcmp(implementacion,"4") == 0)
        return 1;
    else
    {
        printf("\nIngrese una implementacion valida\n\n");
        return 0;
    }
}

