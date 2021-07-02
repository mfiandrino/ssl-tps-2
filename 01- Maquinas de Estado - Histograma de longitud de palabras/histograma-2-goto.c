//#include "histograma.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define IN 1
#define OUT 0

unsigned int *histograma2()
{
    //static unsigned int contadores[10] = {0,3,3};
    printf("\nHas entrado a la implementacion con goto\n");
    int c,nc,state;
    c = nc = 0;
    bool primeraLectura = true;
    state = OUT;
    unsigned int nw[100] = {0};
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































/* Para el README.md Parte del Goto

¿Tiene alguna aplicacion goto hoy en dia?
Los goto se utilizan en lenguaje de bajo nivel para hacer saltos de linea, en C se pueden utilizar para errores o para salir de ciclos multiples. 
¿Algun lenguaje moderno lo utiliza?
Muchos lenguajes tienen GOTO o similares, pero en todos, utilizarlos discriminadamente esta visto como una mala practica de programacion


*/