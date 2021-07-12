#include "histograma.h"

int *implementarHistograma(char *implementacion, unsigned int* contadores, unsigned int cantContadores)
{
    if(strcmp(implementacion,"1") == 0)
        histograma1(contadores,cantContadores);

    else if(strcmp(implementacion,"2") == 0)
        histograma2(contadores,cantContadores);

    else if(strcmp(implementacion,"3") == 0)
        histograma3(contadores,cantContadores);
/*        
    else
        return histograma4();
        */
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

