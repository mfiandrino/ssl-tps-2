#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxPila 100

char pila[maxPila];
int indicePila;

int pop(char*);
int push(char);
int pushString(char*);
char cima();
void inicializarPila();
int estaVacia();

#endif
