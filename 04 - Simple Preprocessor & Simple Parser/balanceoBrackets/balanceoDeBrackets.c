/*
Balanceo de brackets
Archivo main del balanceo de brackets
Grupo Nro 3 del curso K2051 Lunes TN
20210920
*/
#include "funcionesBalanceo.h"
#include <stdio.h>

int main()
{
    int c;
    inicializarPila();

    while ((c = getchar()) != EOF)
    {
        (*fun_ptr)(c);
    }
       
    if (estaVacia())
        printf("\nLos brackets estan balanceados\n");
    else
        manejoDeErrores(BRACKETS_NO_BALANCEADOS);
}

int main()
{
    int c;
    inicializarPila();

    for(;;)
        fun_ptr(getchar());
       
    if (estaVacia())
        printf("\nLos brackets estan balanceados\n");
    else
        manejoDeErrores(BRACKETS_NO_BALANCEADOS);
}


