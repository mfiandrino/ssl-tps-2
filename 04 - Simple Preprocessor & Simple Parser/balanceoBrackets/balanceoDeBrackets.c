/*
Balanceo de brackets
Archivo main del balanceo de brackets
Grupo Nro 3 del curso K2051 Lunes TN
20210905
*/
#include "funcionesBalanceo.h"

int main()
{
    int c;
    inicializarPila();
    int resultado;
    fun_ptr = &caracterComun;
    while ((c = getchar()) != EOF){
        resultado = (*fun_ptr)(c);
        
        if(resultado == -1){
            break;
        }else if(resultado == -2){
            printf("\nError: hay mas de un caracter en unas comillas simples\n");
            break;
        }else if(resultado == -3){
            printf("\nError: hay comillas dentro de comillas simples sin usar la contrabarra\n");
            break;  
        }     
    }
       
    if (!estaVacia() || resultado == -1)
        printf("\nError: los brackets NO estan balanceados\n");
    else if(resultado == 1)
        printf("\nLos brackets estan balanceados\n");       
      
}

