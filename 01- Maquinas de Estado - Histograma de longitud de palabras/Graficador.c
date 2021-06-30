#include "Graficador.h"

void graficarHistograma(char simbolo, unsigned int *contadores , unsigned int cantidadContadores)
{
    printf("\nHISTOGRAMA\n");
    for(int i=0 ; i<cantidadContadores ; i++)
    {
        printf("\n%4d- ",i);
        for (int j=0 ; j<contadores[i] ; j++)
        {
            printf("%c",simbolo);
        }
    }
    printf("\n\n");
}