#include "histograma.h"

unsigned int *histograma3()
{
    static unsigned int contadores[10] = {0,3,7,5,1};
    printf("\nHas entrado a la implementacion recursiva\n");
    return contadores;
}