#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define maxPila 100

char pila[maxPila];
int indicePila;

int pop(char*,char*);
int push(char*, char);
char cima(char*);
void inicializarPila();

#endif