/*
Preprocesador
Archivo main del preprocesador
Grupo Nro 3 del curso K2051 Lunes TN
20210905
*/
#include "funcionesPreprocesador.h"

int main()
{
    int c;
    int resultado;
    
   // fun_ptr = &comienzoDeLinea; //TODO: Sacar el & en los estados
    while ((c=getchar( ))!= EOF) 
    {
        resultado = (*fun_ptr)(c); //TODO: se puede sacar el *
        
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
    }
    if(resultado == 1)
        printf("\nEl proceso ha finalizado con exito\n\n");
}
