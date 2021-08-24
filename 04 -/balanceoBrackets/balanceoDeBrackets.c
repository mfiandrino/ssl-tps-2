/*
Balanceo de brackets
Archivo main del balanceo de brackets
Grupo Nro 3 del curso K2051 Lunes TN
20210824
*/
#include "funcionesBalanceo.h"

int main()
{
    int resultado = balanceoDeBrackets();
    if(resultado == 1)
        printf("\nLos brackets estan balanceados\n");
    else if (resultado == -1)
        printf("\nLos brackets NO estan balanceados\n");
    else
        printf("\nLas comillas NO cierran antes del final\n");
        
}