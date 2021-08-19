#include "stack.h"

static int estaVacia(pila_t*, char);
static int estaLlena(pila_t*);

void push(pila_t *strPila , char dato)
{
    if(!estaLlena(strPila))
    {
        (strPila->indicePila)++;
        strPila->pila[strPila->indicePila] = dato;
        printf("\nEl dato \"%c\" fue agregado correctamente a la pila\n",dato);
    }
    else
        printf("\nLa pila esta llena, no se pueden agregar mas elementos\n");
}

char pop(pila_t *strPila)
{
    char dato;

    if(!estaVacia(strPila,'$'))
    {
        dato = strPila->pila[strPila->indicePila];
        (strPila->indicePila)--;
        printf("\nEl dato \"%c\" fue extraido correctamente de la pila\n",dato);
        return dato;
    }
    else
        printf("\nLa pila esta vacia, no se pueden extraer elementos\n");
}

static int estaVacia(pila_t *strPila , char caracterBase)
{
    if(strPila->pila[strPila->indicePila] == caracterBase)
        return 1;
    return 0;
}

static int estaLlena(pila_t *strPila)
{
    if(strPila->indicePila == maxPila)
        return 1;
    return 0;
}

pila_t *crearPila(char caracterBase)
{
    pila_t *strPila;
    strPila = malloc(sizeof(pila_t));
    strPila->indicePila = 0;
    strPila->pila[strPila->indicePila] = caracterBase;
    (strPila->indicePila)++;
}