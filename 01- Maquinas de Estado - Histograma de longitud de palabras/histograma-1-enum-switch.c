#include "histograma.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    OUT /* fuera de una palabra*/, 
    IN /* dentro de una palabra*/
}state;

unsigned int *histograma1()
{
    printf("\nHas entrado a la implementacion con enum y switch\n");

    state s = OUT;
    static unsigned conts[largoMaxPalabra];
    int c, nc;
    nc = 0;
    while ((c=getchar( ))!= EOF) 
    {
        switch (s){
            case OUT:
                switch (c)
                {
                    case ' ': case '\t': case '\n':
                        s=OUT;
                    break;
                    default:
                        ++nc;
                        s = IN;
                    break;
                }
            break;
            default: /* IN*/
                switch (c)
                {
                    case ' ': case '\t': case '\n':
                        s = OUT;
                        ++conts[nc];                       
                        nc = 0;
                    break;
                    default:
                        ++nc;
                        s = IN;
                    break;
                }
       }
    }
    return conts;
}