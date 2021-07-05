
#include "histograma.h"
#include <string.h>
#include <stdio.h>

int in( int caracter, int contador, unsigned int* nw )
{
     if (caracter == ' ' || caracter == '\n' || caracter == '\t')
     {
         out( caracter,nw, contador);
     }
     else
     {
         printf("%c",caracter);
         contador = in (caracter = getchar(), contador,nw) + 1;
     }

     return contador;
}
void out( int caracter, unsigned int* nw, int contadorCaracter )
{
    ++nw[contadorCaracter];
    printf("%u\n", nw[contadorCaracter]);
    contadorCaracter = 0;
    return nw;
}
unsigned int *histograma3()
{
    printf("\nHas entrado a la implementacion recursiva\n");

    int caracter,nc,state = 0;
    unsigned int nw[100]= {0};

    caracter = getchar();
      if ((caracter == ' ' || caracter == '\n' || caracter == '\t'))
        {
        }
        else
        {
            nc = in(caracter,nc, nw);
            printf("%d\n", nc);
        }

    return nw;
}
