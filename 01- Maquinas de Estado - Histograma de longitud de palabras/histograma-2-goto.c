#include "histograma.h"
#include <string.h>
#include <stdio.h>

unsigned int *histograma2(unsigned int* contadores, unsigned int cantContadores)
//unsigned int *histograma2()
{
    printf("\nHas entrado a la implementacion con goto\n");
    int c;
    c = cantContadores = 0;
    c = getchar();
    if (c == EOF) return contadores;
    else if (c == ' ' || c == '\n' || c == '\t') goto OUT;
    else goto IN;
    OUT:
        ++contadores[cantContadores];
        cantContadores = 0;
        c = getchar ();
        if (c == EOF) return contadores;
        else if (c == ' ' || c == '\n' || c == '\t') goto OUT;
        else goto IN;
    IN:
        ++cantContadores;
        c = getchar ();
        if (c == EOF) return contadores;
        else if (c == ' ' || c == '\n' || c == '\t') goto OUT;
        else goto IN;
        
}
