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


