/*
Balanceo de brackets
Modulo con las funciones para el balanceo de brackets para el TP4.
Grupo Nro 3 del curso K2051 Lunes TN
20210902
*/
#include "funcionesBalanceo.h"

typedef enum {
    CARACTER_COMUN,
    APERTURA_BRACKET,
    CLAUSURA_BRACKET,
    APERTURA_COMILLAS_SIMPLES,
    CARACTER_COMILLAS_SIMPLES,
    CLAUSURA_COMILLAS_SIMPLES,
    APERTURA_COMILLAS_DOBLES,
    CARACTER_COMILLAS_DOBLES,
    CLAUSURA_COMILLAS_DOBLES,
    ERROR_MAS_DE_UN_CARACTER_EN_COMILLAS_SIMPLES,
    ERROR_COMILLAS_DENTRO_DE_COMILLAS_SIMPLES,
    CARACTER_CONTRABARRA_COMILLA_SIMPLE,
    CARACTER_CONTRABARRA_COMILLA_DOBLE,
    BRACKETS_NO_BALANCEADOS
}state;

static char bracketInvertido(char);
static int cierraBracketCorrecto(char, char);
static int atenderClausuraBracket(char*, int);

int balanceoDeBrackets()
{
    int c;
    inicializarPila();
    state s = CARACTER_COMUN;

    while ((c=getchar())!= EOF) 
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
                        if(atenderClausuraBracket(pila,c))
                            s = CLAUSURA_BRACKET;
                        else 
                            s = BRACKETS_NO_BALANCEADOS;
                        break;

                    case '\'':                     
                        s = APERTURA_COMILLAS_SIMPLES;
                        break;      

                    case '\"':
                        s = APERTURA_COMILLAS_DOBLES;
                        break;

                    default: //EOC
                        s = CARACTER_COMUN;                        
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
                        if(atenderClausuraBracket(pila,c))
                            s = CLAUSURA_BRACKET;
                        else 
                            s = BRACKETS_NO_BALANCEADOS;
                        break;
                       
                    case '\'': 
                        s = APERTURA_COMILLAS_SIMPLES;
                        break;
                    
                    case '\"':
                        s = APERTURA_COMILLAS_DOBLES;
                        break;
     
                    default: //EOC
                        s = CARACTER_COMUN;
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
                        if(atenderClausuraBracket(pila,c))
                            s = CLAUSURA_BRACKET;
                        else 
                            s = BRACKETS_NO_BALANCEADOS;
                        break;

                    case '\'': 
                        s = APERTURA_COMILLAS_SIMPLES;
                        break;
                    
                    case '\"':
                        s = APERTURA_COMILLAS_DOBLES;
                        break;
      
                    default: //EOC
                        s = CARACTER_COMUN;
                }
                break;

            case APERTURA_COMILLAS_SIMPLES:
                switch (c)
                {
                    case '\\':
                        s = CARACTER_CONTRABARRA_COMILLA_SIMPLE;
                        break;

                    case '\'': case '\"':
                        s = ERROR_COMILLAS_DENTRO_DE_COMILLAS_SIMPLES;
                        break;

                    default:
                        s = CARACTER_COMILLAS_SIMPLES; 
                }               
                break;

        case CARACTER_COMILLAS_SIMPLES:
            switch (c)
            {
                case '\'':
                    s = CLAUSURA_COMILLAS_SIMPLES;
                    break;

                default: //EOC
                    s = ERROR_MAS_DE_UN_CARACTER_EN_COMILLAS_SIMPLES;
            }
            break;

        case CLAUSURA_COMILLAS_SIMPLES:
            switch (c)
            {
                case '\"':
                    s = APERTURA_COMILLAS_DOBLES;
                    break;

                case '\'':
                    s = APERTURA_COMILLAS_SIMPLES;
                    break;

                case '{': case '[': case '(':
                    s = APERTURA_BRACKET;
                    push(pila,c);
                    break;

                case '}': case ']': case ')':
                    if(atenderClausuraBracket(pila,c))
                        s = CLAUSURA_BRACKET;
                    else 
                        s = BRACKETS_NO_BALANCEADOS;
                    break;

                default: //EOC
                    s = CARACTER_COMUN;
            }
            break;

        case APERTURA_COMILLAS_DOBLES:
            switch (c)
            {
                case '\\':
                    s = CARACTER_CONTRABARRA_COMILLA_DOBLE;
                    break;

                case '\"':
                    s = CLAUSURA_COMILLAS_DOBLES;
                    break;

                default: //EOC
                    s = CARACTER_COMILLAS_DOBLES;
            }
            break;

        case CARACTER_COMILLAS_DOBLES:
            switch (c)
            {
                case '\\':
                    s = CARACTER_CONTRABARRA_COMILLA_DOBLE;
                    break;

                case '\"':
                    s = CLAUSURA_COMILLAS_DOBLES;
                    break;

                default: //EOC
                    s = CARACTER_COMILLAS_DOBLES;
            }
            break;

        case CLAUSURA_COMILLAS_DOBLES:
            switch (c)
            {
                case '\"':
                    s = APERTURA_COMILLAS_DOBLES;
                    break;

                case '\'':
                    s = APERTURA_COMILLAS_SIMPLES;
                    break;

                case '{': case '[': case '(':
                    s = APERTURA_BRACKET;
                    push(pila,c);
                    break;

                case '}': case ']': case ')':
                    if(atenderClausuraBracket(pila,c))
                        s = CLAUSURA_BRACKET;
                    else 
                        s = BRACKETS_NO_BALANCEADOS;
                    break;

                default: //EOC
                    s = CARACTER_COMUN;
            }
            break;

        case CARACTER_CONTRABARRA_COMILLA_SIMPLE:
            s = CARACTER_COMILLAS_SIMPLES;
            break;

        case CARACTER_CONTRABARRA_COMILLA_DOBLE:
            s = CARACTER_COMILLAS_DOBLES; 
            break;

        case BRACKETS_NO_BALANCEADOS:
            return -1; // Error por pila vacia o porque no cierra el bracket correcto

        case ERROR_MAS_DE_UN_CARACTER_EN_COMILLAS_SIMPLES:
            return -2;

        case ERROR_COMILLAS_DENTRO_DE_COMILLAS_SIMPLES:
            return -3;
        }
    }
    return 1;
}

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

static int atenderClausuraBracket(char *pila, int caracter)
{
    char bracket;
    if(pop(pila,&bracket) && cierraBracketCorrecto(caracter,bracket))
        return 1;
    else 
        return 0;
}