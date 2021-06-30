#include "histograma.h"

unsigned int *histograma1()
{
    static unsigned int contadores[10] = {0,1,2,3,5,4,3,2,1,0};
    printf("\nHas entrado a la implementacion con enum y switch\n");
    return contadores;
}