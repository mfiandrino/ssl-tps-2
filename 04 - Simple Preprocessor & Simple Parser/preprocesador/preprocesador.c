/*
Preprocesador
Archivo main del preprocesador
Grupo Nro 3 del curso K2051 Lunes TN
20210911
*/
#include "funcionesPreprocesador.h"
#include <stdio.h>
int main()
{
    int c;
    int resultado;
    
    while ((c=getchar( ))!= EOF) 
    {
        resultado = (fun_ptr)(c);
        
        if(resultado == -1)
        {
            printf("\nError: Un #define o un #undef tienen un Identificador Invalido\n");
            break;
        }
        else if(resultado == -2)
        {
            printf("\nError: Un #define tiene el texto a reemplazar Invalido\n");
            break;
        }
        else if (resultado== -3)
        {
            printf("\nError: Luego del # no hay un define ni undef\n");
            break;
        }
    }
    if(resultado == 1)
        printf("\nEl proceso ha finalizado con exito\n\n");
}
