/*
Balanceo de brackets
Archivo main del balanceo de brackets
Grupo Nro 3 del curso K2051 Lunes TN
20210902
*/
#include "funcionesBalanceo.h"

int main()
{
    int resultado = balanceoDeBrackets(); 
    if(resultado == 1)
        printf("\nLos brackets estan balanceados\n");
    else if(resultado == -1)
        printf("\nError: los brackets NO estan balanceados\n");
    else if(resultado == -2)
        printf("\nError: hay mas de un caracter en unas comillas simples\n");
    else if(resultado == -3)
        printf("\nError: hay comillas dentro de comillas simples sin usar la contrabarra\n");
    
}