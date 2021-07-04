#include "histograma.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

unsigned int *histograma1()
{
    typedef enum {
        OUT /* fuera de una palabra*/, 
        IN /* dentro de una palabra*/
    }STATUS;

    static unsigned int contadores[10] = {0,1,2,3,5,4,3,2,1,0};
    printf("\nHas entrado a la implementacion con enum y switch\n");
    return contadores;

    STATUS state = OUT;
    static unsigned conts[100] = {0};
    int c, nc;
    nc = 0;
    while ((c=getchar( ))!= EOF) {
        switch (state){
            case OUT:
                switch (c){
                    case ' ': case '\t': case '\n':
                        state=OUT;
                    break;
                    default:
                        ++nc;
                        state = IN;
                    break;
                }
            break;
            default: /* IN*/
                switch (c){
                    case ' ': case '\t': case '\n':
                        state = OUT;
                        ++conts[nc];
                        printf("palabra[CantCaracteres]: %d | Cantidad de caracteres: %d\n ", conts[nc],nc);                        
                        nc = 0;
                    break;
                    default:
                        ++nc;
                        state = IN;
                    break;
                }
       }
    }
    return conts;
}

    typedef enum {
        OUT /* fuera de una palabra*/, 
        IN /* dentro de una palabra*/
    }STATUS;

int main(){


    static unsigned int contadores[10] = {0,1,2,3,5,4,3,2,1,0};
    printf("\nHas entrado a la implementacion con enum y switch\n");
    

    STATUS state = OUT;
    static unsigned conts[100] = {0};
    int c, nc;
    nc = 0;
    while ((c=getchar( ))!= EOF) {
        switch (state){
            case OUT:
                switch (c){
                    case ' ': case '\t': case '\n':
                        state=OUT;
                    break;
                    default:
                        ++nc;
                        state = IN;
                    break;
                }
            break;
            default: /* IN*/
                switch (c){
                    case ' ': case '\t': case '\n':
                        state = OUT;
                        ++conts[nc];
                        printf("palabra[CantCaracteres]: %d | Cantidad de caracteres: %d\n ", conts[nc],nc);                        
                        nc = 0;
                    break;
                    default:
                        ++nc;
                        state = IN;
                    break;
                }
       }
    }
    for(int i=0;i<100;i++)
    printf("%d\n",conts[i]);
}