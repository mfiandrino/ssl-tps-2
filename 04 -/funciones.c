/*
Funcionalidades TP
Implementación de las funcionalidades que pide el TP. Balanceo de brackets, reemplazo de comentarios y #defines
Grupo Nro 3 del curso K2051 Lunes TN
20210819
*/
#include "funciones.h"

static char bracketInvertido(char bracket)
{
    switch(bracket)
    {
        case '{':
            return '}';
        case '[':
            return ']';
        default:
            return ')';
    }
}

void balanceoDeBrackets()
{
    pila_t *pila = crearPila('$');
    printf("\nHas entrado al balanceo de brackets\n");
    char dato,c;

    while ((c=getchar())!=EOF)
    {
        if (c == '{' || c == '[' || c == '(')
            goto APERTURA_BRACKET;
        else if (c == '}' || c == ']' || c == ')')
            goto CLAUSURA_BRACKET;
        else
            continue;

        APERTURA_BRACKET:
        push(pila,c);
        continue;

        CLAUSURA_BRACKET:
        dato = bracketInvertido(pop(pila));
        if(dato != c)
        {
            printf("\nLos bracket NO estan balanceados\n");
            return;
        }
        continue;   
    }
    return;
}