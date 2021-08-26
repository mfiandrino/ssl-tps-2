/*
Atender Comentarios
Archivo main de reemplazo de comentarios
Grupo Nro 3 del curso K2051 Lunes TN
*/

#include "funcionesComentarios.h"

int main()
{
    int resultado = atenderComentarios();
    if(resultado == 1)
        printf("\nLos brackets estan balanceados\n");
    else if (resultado == -1)
        printf("\nLos brackets NO estan balanceados\n");
    else
        printf("\nLas comillas NO cierran antes del final\n");
        
}