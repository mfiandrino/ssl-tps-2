#ifndef FUNCIONESPREPROCESADOR_H_INCLUDED
#define FUNCIONESPREPROCESADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

int comienzoDeLinea(int);
extern int (*fun_ptr)(int);

//fun_ptr = &comienzoDeLinea; //TODO: Sacar el & en los estados

#endif

//Mover #includes a los .c Ver paper de interfaces