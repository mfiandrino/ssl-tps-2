/*
Modulo Stack
Implementación de las funciones basicas para manejar pilas
Grupo Nro 3 del curso K2051 Lunes TN
20210902
*/
#include "stack.h"

static int estaVacia(char*);
static int estaLlena(char*);


void inicializarPila()
{
    indicePila = 0;
    push(pila,'$');
}

int push(char *pila , char dato)
{
    if(!estaLlena(pila))
    {
        ++indicePila;
        pila[indicePila] = dato;
        //printf("\nEl dato \"%c\" fue agregado correctamente a la pila\n",dato);
        return 1;
    }
    //printf("\nLa pila esta llena, no se pueden agregar mas elementos\n");
    return 0;
}

int pop(char *pila,char *dato)
{
    if(!estaVacia(pila))
    {
        *dato = pila[indicePila];
        --indicePila;
        //printf("\nEl dato \"%c\" fue extraido correctamente de la pila\n",*dato);
        return 1;
    }

    //printf("\nLa pila esta vacia, no se pueden extraer elementos\n");
    return 0;
}

static int estaVacia(char *pila)
{
    printf("\nEl indice de la pila es: %d\n",indicePila);
    if(pila[indicePila] == '$') //Se podria hacer poniendo como condicion que el indice sea mayor a 0
        return 1;
    return 0;
}

static int estaLlena(char *pila)
{
    if(indicePila == maxPila)
        return 1;
    return 0;
}

char cima(char *pila)
{
    return pila[indicePila];
}
