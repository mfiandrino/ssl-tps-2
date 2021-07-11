
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
         in ( getchar(), cantContadores,contadores);
     }

}
void out( int caracter, int cantContadores, unsigned int* contadores)
{
    if(caracter==EOF)
    {
        printf("\n Fin \n"); //Verificar que es el fin del ingreso de caracteres
    }
    else 
    {
        ++contadores[cantContadores]; 
        cantContadores = 0; 

        in( getchar(),cantContadores,contadores);
    }
    
 
}
void histograma3(unsigned int* contadores, unsigned int cantContadores)
{
    printf("\nHas entrado a la implementacion recursiva\n");

    int caracter = 0;
    caracter = getchar();

      if ((caracter == ' ' || caracter == '\n' || caracter == '\t' || caracter == EOF))
        {
            out(caracter, cantContadores ,contadores);
        }
        else
        {
            in(caracter,cantContadores ,contadores);

        }        
}
