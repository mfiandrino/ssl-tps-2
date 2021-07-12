/*
Histograma enum-switch
Implementación de un histograma utilizando enum para abstraernos del valor de IN y OUT y también la sentencia switch para evaluar cada caso
Grupo Nro 3 del curso K2051 Lunes TN
20210712
*/
#include "histograma.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    OUT /* fuera de una palabra*/, 
    IN /* dentro de una palabra*/
}state;

void histograma1(unsigned int* contadores, unsigned int cantContadores)
{
    printf("\nHas entrado a la implementacion con enum y switch\n");

    state s = OUT;
    int c, nc=0;
    while ((c=getchar( ))!= EOF) 
    {
        switch (s){
            case OUT:
                switch (c)
                {
                    case ' ': case '\t': case '\n':
                        s=OUT;
                    break;
                    default:
                        ++nc;
                        s = IN;
                    break;
                }
            break;
            default: /* IN*/
                switch (c)
                {
                    case ' ': case '\t': case '\n':
                        s = OUT;
                        if(nc >= cantContadores)
                            nc = --cantContadores;
                        ++contadores[nc];                       
                        nc = 0;
                    break;
                    default:
                        ++nc;
                        s = IN;
                    break;
                }
       }
    }
}
