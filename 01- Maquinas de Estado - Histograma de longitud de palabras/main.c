#include "Graficador.h"
#include "histograma.h"
#include <stdio.h>

//No se por que no los reconoce de histograma.h--------------
#define largoMaxPalabra 100
int *implementarHistograma(char *);
int validarHistograma(char *);
//-----------------------------------------------------------

int main (int argc , char *argv[])
{
    if(argc == 2)
    {
        if(validarHistograma(argv[1]))
            graficarHistograma('/',implementarHistograma(argv[1]),largoMaxPalabra); 
    }
    else if(argc > 2)
        printf("\nHas ingresado mas parametros de lo esperado\n\n");
    else
        printf("\nDebes pasar por parametro la implemetacion que desea ejecutar\n\n");
    
    return 0;
}


