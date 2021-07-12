
#include "histograma.h"
#include <string.h>
#include <stdio.h>

static void out(int, int, unsigned int*, int);
static void in(int, int, unsigned int*,int);

void in( int caracter, int nc, unsigned int* contadores, int cantContadores )
{
     if (caracter == ' ' || caracter == '\n' || caracter == '\t' || caracter == EOF)
     {
         out( caracter, nc,contadores, cantContadores);
     }
     else
     {
         ++nc;
         in ( getchar(), nc,contadores, cantContadores);
     }

}
void out( int caracter, int nc, unsigned int* contadores, int cantContadores)
{
    if(caracter!=EOF)
    {
        if(nc >= cantContadores)
        nc = --cantContadores;

        ++contadores[nc]; 
        nc = 0; 

        in( getchar(),nc,contadores, cantContadores);
    }
}
void histograma3(unsigned int* contadores, unsigned int cantContadores)
{
    printf("\nHas entrado a la implementacion recursiva\n");

    int caracter,nc = 0;
    caracter = getchar();

      if ((caracter == ' ' || caracter == '\n' || caracter == '\t' || caracter == EOF))
        {
            out(caracter, nc ,contadores, cantContadores);
        }
        else
        {
            in(caracter,nc ,contadores,cantContadores);
        }   
}

