#include <stdio.h>
#include <stdlib.h>

#define maxPila 5

typedef struct
{
    char pila[maxPila];
    int indicePila;
}pila_t;

char pop(pila_t*);
void push(pila_t*, char);
pila_t *crearPila(char);

