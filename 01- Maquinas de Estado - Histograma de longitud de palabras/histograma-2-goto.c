#include "histograma.h"
#include <string.h>
#include <stdio.h>

unsigned int *histograma2(unsigned int* contadores, unsigned int cantContadores)
//unsigned int *histograma2()
{
    printf("\nHas entrado a la implementacion con goto\n");
    int c, nc;
    c = nc = 0;
    c = getchar();
    if (c == EOF) return contadores;
    else if (c == ' ' || c == '\n' || c == '\t') goto OUT;
    else goto IN;
    OUT:
         if(nc >= cantContadores)
             nc = --cantContadores;
        ++contadores[nc];
        nc = 0;
        c = getchar ();
        if (c == EOF) return contadores;
        else if (c == ' ' || c == '\n' || c == '\t') goto OUT;
        else goto IN;
    IN:
        ++nc;
        c = getchar ();
        if (c == EOF) return contadores;
        else if (c == ' ' || c == '\n' || c == '\t') goto OUT;
        else goto IN;
        
}
