/*
Balanceo de brackets
Archivo main del balanceo de brackets
Grupo Nro 3 del curso K2051 Lunes TN
20210822
*/
#include "funcionesBalanceo.h"

int main()
{
    int resultado = balanceoDeBrackets2();
    if(resultado == 1)
        printf("\nLos brackets estan balanceados\n");
    else if (resultado == 0)
        printf("\nLos brackets NO estan balanceados\n");
    else
        printf("\nLas comillas NO estan balanceadas\n");
        
}