#include "histograma.h"

unsigned int *histograma2()
{
    static unsigned int contadores[10] = {0,3,3};
    printf("\nHas entrado a la implementacion con goto\n");
    return contadores;
}