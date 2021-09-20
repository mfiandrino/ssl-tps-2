/*
Preprocesador
Archivo main del preprocesador
Grupo Nro 3 del curso K2051 Lunes TN
20210914
*/
#include "funcionesPreprocesador.h"
#include <stdio.h>
int main()
{
    int c;
    
    while ((c=getchar( ))!= EOF) 
    {
        (fun_ptr)(c);
    }
    printf("\nEl proceso ha finalizado con exito\n\n");
}
