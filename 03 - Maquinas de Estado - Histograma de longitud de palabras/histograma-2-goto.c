/*
Histograma goto
Implementación de un histograma utilizando la sentencia goto
Grupo Nro 3 del curso K2051 Lunes TN
20210712
*/
#include "histograma.h"
#include <string.h>
#include <stdio.h>

void histograma2(unsigned int* contadores, unsigned int cantContadores)
{
    printf("\nHas entrado a la implementacion con goto\n");
    int c, nc;
    c = nc = 0;
    c = getchar();
    if (c == EOF) return;
    else if (c == ' ' || c == '\n' || c == '\t') goto OUT;
    else goto IN;
    OUT:
         if(nc >= cantContadores)
             nc = --cantContadores;
        ++contadores[nc];
        nc = 0;
        c = getchar ();
        if (c == EOF) return;
        else if (c == ' ' || c == '\n' || c == '\t') goto OUT;
        else goto IN;
    IN:
        ++nc;
        c = getchar ();
        if (c == EOF) return;
        else if (c == ' ' || c == '\n' || c == '\t') goto OUT;
        else goto IN;  
}
