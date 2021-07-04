#include "Graficador.h"

static unsigned int palabraMasLarga (unsigned int*, unsigned int);

void graficarHistograma(char simbolo, unsigned int *contadores , unsigned int cantidadContadores)
{
    cantidadContadores = palabraMasLarga(contadores,cantidadContadores);

    printf("\nHISTOGRAMA\n");
    if(cantidadContadores == 0)
        printf("\nNo se ha ingresado ninguna palabra");
    else
    {
        for(int i=1 ; i<=cantidadContadores ; i++)
        {
            printf("\n%4d- ",i);
            for (int j=0 ; j<contadores[i] ; j++)
            {
                printf("%c",simbolo);
            }
        }
    }
    printf("\n\n");
}

static unsigned int palabraMasLarga (unsigned int *contadores , unsigned int cantidadContadores)
{
    for(--cantidadContadores ; cantidadContadores != 0 && contadores[cantidadContadores] == 0; cantidadContadores--);
    return cantidadContadores;
}