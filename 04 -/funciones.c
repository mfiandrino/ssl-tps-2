/*
Funcionalidades TP
Implementación de las funcionalidades que pide el TP. Balanceo de brackets, reemplazo de comentarios y #defines
Grupo Nro 3 del curso K2051 Lunes TN
20210819
*/
#include "funciones.h"

typedef enum {
    CARACTER_COMUN,
    APERTURA_BRACKET, 
    CLAUSURA_BRACKET,
    COMILLAS,
}state;

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


int balanceoDeBrackets2()
{
    pila_t *pila = crearPila('$');
    printf("\nHas entrado al balanceo de brackets2\n");
    char bracket;
    int c;
    int cAux;

    state s = CARACTER_COMUN;

    while ((c=getchar( ))!= EOF) 
    {
        switch (s)
        {
            case CARACTER_COMUN:
                switch (c)
                {
                    case '{': case '[': case '(':
                        s = APERTURA_BRACKET;
                        push(pila,c);
                    break;

                    case '}': case ']': case ')':
                        s = CLAUSURA_BRACKET;
                        if(pop(pila,&bracket) && cierraBracketCorrecto(c,bracket))
                            break;
                        else 
                            return 0;

                    case '\'': case '\"':
                        printf("\nEntro al caso comillas");
                        s = COMILLAS;
                        cAux = c;
                        while ((c=getchar())!=EOF)
                        {
                            if(c == '\\')
                                getchar();
                            if(c == cAux)
                                break;
                        }
                        if (c == EOF)
                            return 2;
                    break;

                    default: //CARACTER_COMUN
                        s = CARACTER_COMUN;
                    break;
                }
            break;

            case APERTURA_BRACKET:
                switch (c)
                {
                    case '{': case '[': case '(':
                        s = APERTURA_BRACKET;
                        push(pila,c);
                    break;

                    case '}': case ']': case ')':
                        s = CLAUSURA_BRACKET;
                        if(pop(pila,&bracket) && cierraBracketCorrecto(c,bracket))
                            break;
                        else 
                            return 0;

                    case '\'': case '\"':
                        s = COMILLAS;
                        cAux = c;
                        while ((c=getchar())!=EOF)
                        {
                            if(c == '\\')
                                getchar();
                            if(c == cAux)
                                break;
                        }
                        if (c == EOF)
                            return 2;
                    break;

                    default: //CARACTER_COMUN
                        s = CARACTER_COMUN;
                    break;
                }
            break;

            case CLAUSURA_BRACKET:
                switch (c)
                {
                    case '{': case '[': case '(':
                        s = APERTURA_BRACKET;
                        push(pila,c);
                    break;

                    case '}': case ']': case ')':
                        s = CLAUSURA_BRACKET;
                        if(pop(pila,&bracket) && cierraBracketCorrecto(c,bracket))
                            break;
                        else 
                            return 0;

                    case '\'': case '\"':
                        s = COMILLAS;
                        cAux = c;
                        while ((c=getchar())!=EOF)
                        {
                            if(c == '\\')
                                getchar();
                            if(c == cAux)
                                break;
                        }
                        if (c == EOF)
                            return 2;
                    break;

                    default: //CARACTER_COMUN
                        s = CARACTER_COMUN;
                    break;
                }
            break;

            case COMILLAS:
                switch (c)
                {
                    case '{': case '[': case '(':
                        s = APERTURA_BRACKET;
                        push(pila,c);
                    break;

                    case '}': case ']': case ')':
                        s = CLAUSURA_BRACKET;
                        if(pop(pila,&bracket) && cierraBracketCorrecto(c,bracket))
                            break;
                        else 
                            return 0;

                    case '\'': case '\"':
                        s = COMILLAS;
                        cAux = c;
                        while ((c=getchar())!=EOF)
                        {
                            if(c == '\\')
                                getchar();
                            if(c == cAux)
                                break;
                        }
                        if (c == EOF)
                            return 2;
                    break;

                    default: //CARACTER_COMUN
                        s = CARACTER_COMUN;
                    break;
                }
            break;
       }
    }
    return 1;
}




int balanceoDeBrackets()
{
    pila_t *pila = crearPila('$');
    printf("\nHas entrado al balanceo de brackets\n");
    char bracket;
    int c;
    int cAux;

    while ((c=getchar())!=EOF)
    {
        if (c == '{' || c == '[' || c == '(')
            goto APERTURA_BRACKET;
        else if (c == '}' || c == ']' || c == ')')
            goto CLAUSURA_BRACKET;
        else if  (c ==  '\'' || c == '\"' )
             goto CASO_ESPECIAL;
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

        CASO_ESPECIAL:
        cAux = c;
         while ((c=getchar())!=EOF){

             if(c == '\\')
                getchar();

            if  ( c == cAux)
                break;
        }
        if (c == EOF){
            return 2;
        }
    }
    return 1;
}