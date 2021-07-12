/*
Programa Main
El Main será de donde arranque el programa principal, de donde se coordinará qué histograma se va a usar y luego imprimirá su gráfico.
Grupo Nro 3 del curso K2051 Lunes TN
20210712
*/

#include "Graficador.h"
#include "histograma.h"
#include <stdio.h>

int main (int argc , char *argv[])
{
    unsigned int contadores[largoMaxPalabra+1] = {0};
    if(argc == 2)
    {
        if(validarHistograma(argv[1]))
        {
            implementarHistograma(argv[1],contadores,largoMaxPalabra+1);
            graficarHistograma('/',contadores,largoMaxPalabra+1);
        }
    }
    else if(argc > 2)
        printf("\nHas ingresado mas parametros de lo esperado\n\n");
    else
        printf("\nDebes pasar por parametro la implemetacion que desea ejecutar\n\n");
    
    return 0;
}


