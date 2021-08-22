/*
Modulo Stack
Implementación de las funciones basicas para manejar pilas
Grupo Nro 3 del curso K2051 Lunes TN
20210819
*/
#include "stack.h"

static int estaVacia(pila_t*, char);
static int estaLlena(pila_t*);

int push(pila_t *strPila , char dato)
{
    if(!estaLlena(strPila))
    {
        (strPila->indicePila)++;
        strPila->pila[strPila->indicePila] = dato;
        printf("\nEl dato \"%c\" fue agregado correctamente a la pila\n",dato);
        return 1;
    }
    printf("\nLa pila esta llena, no se pueden agregar mas elementos\n");
    return 0;
}

int pop(pila_t *strPila,char *dato)
{
    if(!estaVacia(strPila,'$'))
    {
        *dato = strPila->pila[strPila->indicePila];
        (strPila->indicePila)--;
        printf("\nEl dato \"%c\" fue extraido correctamente de la pila\n",*dato);
        return 1;
    }

    printf("\nLa pila esta vacia, no se pueden extraer elementos\n");
    return 0;
}

static int estaVacia(pila_t *strPila , char caracterBase)
{
    printf("\nEl indice de la pila es: %d\n",strPila->indicePila);
    if(strPila->pila[strPila->indicePila] == caracterBase) //Se podria hacer poniendo como condicion que el indice sea mayor a 0
        return 1;
    return 0;
}

static int estaLlena(pila_t *strPila)
{
    if(strPila->indicePila == maxPila)
        return 1;
    return 0;
}

char cima(pila_t *strPila)
{
    return strPila->pila[strPila->indicePila];
}

pila_t *crearPila(char caracterBase)
{
    pila_t *strPila;
    strPila = malloc(sizeof(pila_t));
    strPila->indicePila = 0;
    strPila->pila[strPila->indicePila] = caracterBase;
    return strPila;
}