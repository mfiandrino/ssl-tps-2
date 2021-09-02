/*
Balanceo de brackets
Modulo con las funciones para el balanceo de brackets para el TP4.
Grupo Nro 3 del curso K2051 Lunes TN
20210824
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
    CARACTER_CONTRABARRA,
}state;

static char bracketInvertido(char);
static int cierraBracketCorrecto(char, char);
static void atenderAperturaBracket(pila_t*, int, state*);
static int atenderClausuraBracket(pila_t*, int, state*);
static int atenderComillas(int,state *);
//Ir a la funcion atenderComillas cada vez que entra un caracter en la maquina de estado y apilar la primer comilla?

int balanceoDeBrackets()
{
    int c;
    pila_t *pila = crearPila('$');
    state s = CARACTER_COMUN;

    while ((c=getchar())!= EOF) 
    {
        switch (s)
        {
            case APERTURA_BRACKET:
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
                    break;

                    case '}': case ']': case ')':
                        s = CLAUSURA_BRACKET;
                    break;

                    default: //EOC
                        s = CARACTER_COMUN;
                }
            break;

        case APERTURA_COMILLAS_DOBLES:
            switch (c)
                {
                    case '\\':
                        s = CARACTER_CONTRABARRA;
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
                        s = CARACTER_CONTRABARRA;
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
                    break;

                    case '}': case ']': case ')':
                        s = CLAUSURA_BRACKET;
                    break;

                    default: //EOC
                        s = CARACTER_COMUN;
                }
            break;

        case CARACTER_CONTRABARRA:
            switch (c)
                {
                    case '\"':
                        s = APERTURA_COMILLAS_DOBLES;
                    break;

                    default: //EOC
                        s = CARACTER_COMUN;
                }
            break;
        }
    }

}

int balanceoDeBrackets2()
{
    pila_t *pila = crearPila('$');
    int c;

    state s = CARACTER_COMUN;

    while ((c=getchar())!= EOF) 
    {
        switch (s)
        {
            case APERTURA_BRACKET:
                switch (c)
                {
                    case '{': case '[': case '(':
                        atenderAperturaBracket(pila,c,&s);
                    break;

                    case '}': case ']': case ')':
                        if(atenderClausuraBracket(pila,c,&s))
                            break;
                        else 
                            return -1; // Error por pila vacia o porque no cierra el bracket correcto

                    case '\'': case '\"':
                        if(atenderComillas(c,&s))
                            break;
                        else
                            return -2; // Error porque llega a EOF sin cerrar comillas

                    default: //EOC
                        s = CARACTER_COMUN;
                }
            break;

            case CLAUSURA_BRACKET:
                switch (c)
                {
                    case '{': case '[': case '(':
                        atenderAperturaBracket(pila,c,&s);
                    break;

                    case '}': case ']': case ')':
                        if(atenderClausuraBracket(pila,c,&s))
                            break;
                        else 
                            return -1; // Error por pila vacia o porque no cierra el bracket correcto

                    case '\'': case '\"':
                        if(atenderComillas(c,&s))
                            break;
                        else
                            return -2; // Error porque llega a EOF sin cerrar comillas

                    default: //EOC
                        s = CARACTER_COMUN;
                }
            break;

            case COMILLAS:
                switch (c)
                {
                    case '{': case '[': case '(':
                        atenderAperturaBracket(pila,c,&s);
                    break;

                    case '}': case ']': case ')':
                        if(atenderClausuraBracket(pila,c,&s))
                            break;
                        else 
                            return -1; // Error por pila vacia o porque no cierra el bracket correcto

                    case '\'': case '\"':
                        if(atenderComillas(c,&s))
                            break;
                        else
                            return -2; // Error porque llega a EOF sin cerrar comillas

                    default: //EOC
                        s = CARACTER_COMUN;
                }
            break;

            default: //Estado CARACTER_COMUN
            case CARACTER_COMUN:
                switch (c)
                {
                    case '{': case '[': case '(':
                        atenderAperturaBracket(pila,c,&s);
                    break;

                    case '}': case ']': case ')':
                        if(atenderClausuraBracket(pila,c,&s))
                            break;
                        else 
                            return -1; // Error por pila vacia o porque no cierra el bracket correcto

                    case '\'': case '\"':
                        if(atenderComillas(c,&s))
                            break;
                        else
                            return -2; // Error porque llega a EOF sin cerrar comillas

                    default: //EOC
                        s = CARACTER_COMUN;
                }
            break;
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

static void atenderAperturaBracket(pila_t *pila, int caracter, state *estado)
{
    *estado = APERTURA_BRACKET;
    push(pila,caracter);
}

static int atenderClausuraBracket(pila_t *pila, int caracter, state *estado)
{
    char bracket;
    *estado = CLAUSURA_BRACKET;
    if(pop(pila,&bracket) && cierraBracketCorrecto(caracter,bracket))
        return 1;
    else 
        return 0;
}

static int atenderComillas(int caracter,state *estado)
{
    int caracterAux;
    *estado = COMILLAS;
    caracterAux = caracter;
    while ((caracter=getchar())!=EOF)
    {
        if(caracter == '\\') //En caso de que el codigo haga referencia a la comilla simple o doble \' \"
            getchar(); // Ignoro el siguiente caracter
        if(caracter == caracterAux) //Si cierran las comillas
            return 1;
    }
    if (caracter == EOF) //Si no encontre la comilla que cierra y llegue a EOF
        return 0;
}
