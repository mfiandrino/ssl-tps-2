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

void out(int c)
{
    int nc=0;
    switch (c)
    {
        case ' ': case '\t': case '\n':
            void (*fun_ptr)(int) = &out;
        break;
        default:
            ++nc;
             void (*fun_ptr)(int) = &in;
    }
}
     

void in(int c)
{
    int nc, cantContadores =0;
    int contadores[100];
    switch (c)
    {
        case ' ': case '\t': case '\n':
           void (*fun_ptr)(int) = &out;
            if(nc >= cantContadores)
            {
                nc = --cantContadores;
                ++contadores[nc];                       
                nc = 0;
            }
        break;
        default:
            ++nc;
            void (*fun_ptr)(int) = &in;

    }
}

void histograma1(unsigned int* contadores, unsigned int cantContadores)
{
    printf("\nHas entrado a la implementacion con enum y switch\n");

    void (*fun_ptr)(int) = &out;
    int c, nc=0;
    while ((c=getchar( ))!= EOF) 
    {
        (*fun_ptr)(c);

    }
}

