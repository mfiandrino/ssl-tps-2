#include "histograma.h"
#include <stdio.h>

unsigned int *histograma1()
{
    static unsigned int contadores[10] = {0,1,2,3,5,4,3,2,1,0};
    printf("\nHas entrado a la implementacion con enum y switch\n");
    return contadores;
}

typedef enum {
    OUT /* fuera de una palabra*/, 
    IN /* dentro de una palabra*/
}STATUS;


void main()
{
    STATUS state = OUT;
    //unsigned nw[100];
    int c, nc;
    nc = 0;
    while ((c=getchar( ))!= EOF) {
        //FILE *fp = fopen("text.txt","w");
        switch (state){
            case OUT:
                switch (c){
                    case ' ': case '\t': case '\n':
                        state=OUT;
                    break;
                    default:
                        ++nc;
                        state = IN;
                        printf("nc1 : %d ", nc, "\n");
                    break;
                }
            break;
            default: /* IN*/
                switch (c){
                    case ' ': case '\t': case '\n':
                        state = OUT;
                        //++nw[nc];
                        //fputs(nw[nc], fp);
                        printf("nc2 : %d ", nc, "\n");
                        //printf("nw[nc]: %d ", nw[nc], "\n");                        
                        nc = 0;
                    break;
                    default:
                        ++nc;
                        state = IN;
                    break;
                }
       }
       //fclose(fp);
    }
}
/* Falta guardar los datos en archivo txt y ver el tema de los arrays. */