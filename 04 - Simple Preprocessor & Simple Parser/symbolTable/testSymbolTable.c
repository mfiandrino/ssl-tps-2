/*
Test Modulo Symbol Table
Pruebas de las funciones del modulo Symbol Table
Grupo Nro 3 del curso K2051 Lunes TN
20210905
*/
#include "symbolTable.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    printf("\nComienzo de test del modulo symbolTable\n");

    //Test de la funcion set
    assert(strcmp("1",set("UNO","1")) == 0);
    assert(strcmp("2",set("DOS","2")) == 0);
    assert(strcmp("4",set("TRES","3")) != 0);
    assert(strcmp("4",set("CUATRO","4")) == 0);
    assert(strcmp("10",set("CINCO","5")) != 0);
    assert(strcmp("hola",set("SEIS","6")) != 0);
    assert(strcmp("7",set("SIETE","7")) == 0);
    assert(strcmp("8",set("OCHO","8")) == 0);
    assert(strcmp("9",set("NUEVE","9")) == 0);
    assert(strcmp("100",set("DIEZ","10")) != 0);

    //Test de la funcion "get"
    assert(strcmp("1",get("UNO")) == 0);
    assert(strcmp("2",get("OCHO")) != 0);
    assert(strcmp("3",get("TRES")) == 0);
    assert(strcmp("4",get("DOS")) != 0);
    assert(strcmp("5",get("CINCO")) == 0);
    assert(strcmp("6",get("SEIS")) == 0);
    assert(strcmp("7",get("NUEVE")) != 0);
    assert(strcmp("8",get("OCHO")) == 0);
    assert(strcmp("9",get("NUEVE")) == 0);
    assert(strcmp("10",get("UNO")) != 0);

    assert(get("UNO") != NULL);
    assert(get("VEINTE") == NULL);
    assert(get("OCHO") != NULL);
    assert(get("MENOSUNO") == NULL);
    assert(get("DIEZ") != NULL);

    //Test de la funcion "delete"
    assert(delete("UNO") != NULL);
    assert(get("UNO") == NULL);

    assert(delete("VEINTE") == NULL);

    assert(delete("OCHO") != NULL);
    assert(get("OCHO") == NULL);

    assert(delete("MENOSUNO") == NULL);

    assert(delete("DIEZ") != NULL);
    assert(get("DIEZ") == NULL);

    
    assert(strcmp("3",delete("TRES")) == 0);
    assert(strcmp("4",delete("DOS")) != 0);
    assert(strcmp("5",delete("CINCO")) == 0);
    assert(strcmp("6",delete("SEIS")) == 0);
    assert(strcmp("7",delete("NUEVE")) != 0);
    

    printf("\nLos test se ejecutaron correctamente\n\n");
}