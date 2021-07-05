#include "histograma.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define IN 1
#define OUT 0

unsigned int *histograma2()
{
    printf("\nHas entrado a la implementacion con goto\n");
    int c,nc,state;
    c = nc = 0;
    bool primeraLectura = true;
    state = OUT;
    static unsigned int nw[largoMaxPalabra] = {0};
    while ((c=getchar())!=EOF){
        if ((c == ' ' || c == '\n' || c == '\t')||(state == OUT)){
            goto fueraDePalabra;
        }
        else{
            goto dentroDePalabra;
        }
        fueraDePalabra:
            if (primeraLectura == false && nc >= 1){
                ++nw[nc];
                //printf("palabra[CantCaracteres]: %d | Cantidad de caracteres: %d\n ", nw[nc],nc);
                nc = 0;
                state = OUT;
                
            }
            primeraLectura = false;
        dentroDePalabra:
            if (c != ' ' && c != '\n' && c != '\t'){
            //printf ("c:%c\n",c);
            ++nc;
            state = IN;
            }
    }
    return nw;
}
