
#include "histograma.h"
#include <string.h>
#include <stdio.h>

int in( int caracter, int contador, unsigned int* nw )
{
     if (caracter == ' ' || caracter == '\n' || caracter == '\t' || caracter == EOF)
     {
         out( caracter, contador,nw);
     }
     else
     {
         ++contador;
         printf("%c espacio %d \n",caracter,contador); // Para ver si recorr�a correctamente el bucle
         in (caracter = getchar(), contador,nw);
     }

     return nw;
}
void out( int caracter, int contadorCaracter, unsigned int* nw)
{
    printf("\n%c\n",caracter);
    if(caracter==EOF)
    {
        printf("\n fin \n"); //PAra verificar si con eof entra al cierre.
        return nw;
    }
    ++nw[contadorCaracter]; //En el array con N caracteres sumo 1
    printf("\nPalabra: %u con %d caracteres \n", nw[contadorCaracter],contadorCaracter); //muestro el valor de ese Array
    contadorCaracter = 0; // lo vuelvo cero para iniciar el bucle.
    caracter = getchar();
    in(caracter,contadorCaracter,nw);
    // return nw; -> No tengo muy en claro si este return va, creer�a que no hace falta
}
unsigned int *histograma3()
{
    printf("\nHas entrado a la implementacion recursiva\n");

    int caracter,nc;
    unsigned int nw[100]= {0};

    caracter = getchar();
      if ((caracter == ' ' || caracter == '\n' || caracter == '\t' || caracter == EOF))
        {
            out ( caracter, nc,nw);
        }
        else
        {
            in(caracter,nc, nw);

        }
for(int c = 0;c<10;c++) // Puse esto para comprobar que al final lleguen los valores de nw
        {
            unsigned int nw2= nw[c];
            printf("\n%d Palabras con: %u",c,nw2);
        }
    return nw;
}
