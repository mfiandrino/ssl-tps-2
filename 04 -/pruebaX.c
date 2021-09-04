/*
Histograma enum-switch
Implementación de un histograma utilizando enum para abstraernos del valor de IN y OUT y también la sentencia switch para evaluar cada caso
Grupo Nro 3 del curso K2051 Lunes TN
20210712
*/
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void (*fun_ptr)(unsigned int*,int,int*,unsigned int*);
void in(unsigned int*,int,int*,unsigned int *);
void out(unsigned int*,int,int*,unsigned int *);

static unsigned int palabraMasLarga (unsigned int*, unsigned int);

void graficarHistograma(char simbolo, unsigned int *contadores , unsigned int cantidadContadores)
{

    cantidadContadores = palabraMasLarga(contadores,cantidadContadores);

    printf("\nHISTOGRAMA\n");
    if(cantidadContadores == 0)
        printf("\nNo se ha ingresado ninguna palabra");
    else
    {
        for(int i=1 ; i<=cantidadContadores ; i++)
        {
            printf("\n%4d- ",i);
            for (int j=0 ; j<contadores[i] ; j++)
            {
                printf("%c",simbolo);
            }
        }
    }
    printf("\n\n");
}

static unsigned int palabraMasLarga (unsigned int *contadores , unsigned int cantidadContadores)
{
    for(--cantidadContadores ; cantidadContadores != 0 && contadores[cantidadContadores] == 0; cantidadContadores--);
    return cantidadContadores;
}

void out(unsigned int* contadores, int c, int *nc, unsigned int *cantContadores)
{
    switch (c)
    {
        case ' ': case '\t': case '\n':
            fun_ptr = &out;
        break;
        default:
            ++(*nc);
            fun_ptr = &in;
    }
}
     

void in(unsigned int* contadores,int c,int *nc, unsigned int *cantContadores)
{
    switch (c)
    {
        case ' ': case '\t': case '\n':
            fun_ptr = &out;
            if(*nc >= *cantContadores)            
                *nc = --(*cantContadores);
            ++contadores[*nc];                       
            *nc = 0;
            break;

        default:
            ++(*nc);
            fun_ptr = &in;
    }
}

void histograma1(unsigned int* contadores, unsigned int cantContadores)
{
    printf("\nHas entrado a la implementacion X\n");
    fun_ptr = &out;
    int c, nc=0;
    while ((c=getchar( ))!= EOF) 
    {
        (*fun_ptr)(contadores,c,&nc,&cantContadores);
    }
}

#define largoMaxPalabra 100

int main()
{
    unsigned int contadores[largoMaxPalabra+1] = {0};
    histograma1(contadores,largoMaxPalabra+1);
    graficarHistograma('/',contadores,largoMaxPalabra+1);
}

