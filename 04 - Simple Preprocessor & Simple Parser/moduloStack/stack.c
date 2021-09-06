/*
Modulo Stack
Implementación de las funciones basicas para manejar una pila
Grupo Nro 3 del curso K2051 Lunes TN
20210905
*/
#include "stack.h"

static int estaVacia();
static int estaLlena();
static int entraString(char*);


void inicializarPila()
{
    indicePila = 0;
    push('$');
}

int push(char dato)
{
    if(!estaLlena())
    {
        ++indicePila;
        pila[indicePila] = dato;
        return 1;
    }
    return 0;
}

int pushString(char *dato)
{
    if(entraString(dato))
    {
        for(int i=0 ; *(dato+i) != '\0' ; i++)
            push(*(dato+i));
        return 1; //ver
    }
    return 0;
}

int pop(char *dato)
{
    if(!estaVacia())
    {
        *dato = pila[indicePila];
        --indicePila;
        return 1;
    }
    return 0;
}

static int estaVacia()
{
    printf("\nEl indice de la pila es: %d\n",indicePila);
    if(pila[indicePila] == '$')
        return 1;
    return 0;
}

static int estaLlena()
{
    if(indicePila + 1 == maxPila)
        return 1;
    return 0;
}

static int entraString(char *string)
{
    if(indicePila + strlen(string) < maxPila)
        return 1;
    return 0;
}

char cima()
{
    return pila[indicePila];
}
