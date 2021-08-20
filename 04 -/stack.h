#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define maxPila 5

typedef struct
{
    char pila[maxPila];
    int indicePila;
}pila_t;

int pop(pila_t*,char*);
int push(pila_t*, char);
pila_t *crearPila(char);

#endif