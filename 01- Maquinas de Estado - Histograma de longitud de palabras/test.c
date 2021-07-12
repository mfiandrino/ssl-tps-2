#include <assert.h>
#include <stdio.h>

#include "histograma.h"

int  main(void){

    unsigned int contadores[largoMaxPalabra+1] = {0};

    implementarHistograma(1,contadores,largoMaxPalabra+1);
    graficarHistograma('/',contadores,largoMaxPalabra+1);    
    
return 0;
}