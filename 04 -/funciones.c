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

static int cierraBracketCorrecto(char c, char bracket)
{
    bracket = bracketInvertido(bracket);
    if(bracket == c)
        return 1;
    return 0;
}


int balanceoDeBrackets()
{
    pila_t *pila = crearPila('$');
    printf("\nHas entrado al balanceo de brackets\n");
    char bracket,c;

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
        if(pop(pila,&bracket) && cierraBracketCorrecto(c,bracket))
            continue;
        else 
            return 0;
    }
    return 1;
}