
#include "histograma.h"
#include <string.h>
#include <stdio.h>

void histograma4(unsigned int* contadores,unsigned int cantContadores)
{
    printf("\nHas entrado a la implementacion x\n");
    int c,nc;
    c = nc = 0;
    while ((c=getchar())!=EOF){
        if ((c == ' ' || c == '\n' || c == '\t')) goto OUT;
        else goto IN;
        
        OUT:
            if(nc >= cantContadores)
                nc = --cantContadores;
            ++contadores[nc];
            nc = 0;
        IN:
            if (c != ' ' && c != '\n' && c != '\t'){
            ++nc;
            }
    }
    return;
}
