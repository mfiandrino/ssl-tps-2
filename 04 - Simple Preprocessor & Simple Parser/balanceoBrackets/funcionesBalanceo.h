#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "../moduloStack/stack.h"

typedef enum {
    MAS_DE_UN_CARACTER_EN_COMILLAS_SIMPLES,
    COMILLAS_DENTRO_DE_COMILLAS_SIMPLES,
    BRACKETS_NO_BALANCEADOS
}error;

void manejoDeErrores(error);

extern void (*fun_ptr)(int);

#endif
