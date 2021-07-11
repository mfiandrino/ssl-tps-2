
#include "histograma.h"
#include <string.h>
#include <stdio.h>

static void out(int, int, unsigned int*);
static void in(int, int, unsigned int*);

void in( int caracter, int cantContadores, unsigned int* contadores )
{
     if (caracter == ' ' || caracter == '\n' || caracter == '\t' || caracter == EOF)
     {
         out( caracter, cantContadores,contadores);
     }
     else
     {
         ++cantContadores;
         in ( caracter = getchar(), cantContadores,contadores);
     }

}
void out( int caracter, int cantContadores, unsigned int* contadores)
{
    if(caracter!=EOF)
    {
        ++contadores[cantContadores]; 
        cantContadores = 0; 

        in( caracter = getchar(),cantContadores,contadores);
    }
}
void histograma3(unsigned int* contadores, unsigned int cantContadores)
{
    printf("\nHas entrado a la implementacion recursiva\n");

    int caracter = 0;
    int nc=0;
    caracter = getchar();

      if ((caracter == ' ' || caracter == '\n' || caracter == '\t' || caracter == EOF))
        {
            out(caracter, nc ,contadores);
        }
        else
        {
            in(caracter,nc ,contadores);
        }   

    for(int c = 0;c<10;c++) // Puse esto para comprobar que al final lleguen los valores de nw
        {
            unsigned int nw2= contadores[c];
            printf("\n%d Palabras con: %u",nw2,c);
        }   
}

