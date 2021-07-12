#include <assert.h>
#include <stdio.h>

#include "histograma.h"
#include "Graficador.h"

int  main(void){

    unsigned int contadores[largoMaxPalabra+1] = {0};
    //char texto = ["hola como andan ? hola dfc 1"];
    //fputs (texto,stdin);
    implementarHistograma("1",contadores,largoMaxPalabra+1);
    graficarHistograma('/',contadores,largoMaxPalabra+1);    
    
return 0;
}