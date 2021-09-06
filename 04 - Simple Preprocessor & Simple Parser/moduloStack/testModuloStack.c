/*
Test Modulo Stack
Pruebas de las funciones del modulo stack
Grupo Nro 3 del curso K2051 Lunes TN
20210905
*/
#include "stack.h"
#include <assert.h>

int main()
{
    printf("\nComienzo de test del modulo symbolTable\n");

    inicializarPila();
    char letra;

    assert(pop(&letra) == 0); //La pila esta vacia, pop devuelve cero avisando del error
    assert(pop(&letra) == 0);
    assert(pop(&letra) == 0);

    assert(pushString("modulo") == 1); // En la pila entra el nuevo string, por lo tanto pushString devuelve 1 avisando del exito del pushString

    assert(push('s') == 1); //La pila no esta llena, por lo tanto push devuelve 1 avisando del exito del push
    assert(push('t') == 1);
    assert(push('a') == 1);
    assert(push('c') == 1);
    assert(push('k') == 1);

    assert(pop(&letra) == 1); //La pila no esta vacia, pop devuelve 1 avisando del exito
    assert(letra == 'k');
    assert(pop(&letra) == 1);
    assert(letra == 'c');
    assert(pop(&letra) == 1);
    assert(letra != 'h');
    assert(pop(&letra) == 1);
    assert(letra == 't');
    assert(pop(&letra) == 1);
    assert(letra == 's');
    assert(pop(&letra) == 1);
    assert(letra != 'k');
    assert(pop(&letra) == 1);
    assert(letra == 'l');
    assert(pop(&letra) == 1);
    assert(letra != '@');
    assert(pop(&letra) == 1);
    assert(letra == 'd');
    assert(pop(&letra) == 1);
    assert(letra == 'o');
    assert(pop(&letra) == 1);
    assert(letra == 'm');

    assert(pop(&letra) == 0); //La pila esta vacia, pop devuelve cero avisando del error
    
    printf("\nLos test se ejecutaron correctamente\n\n");
}