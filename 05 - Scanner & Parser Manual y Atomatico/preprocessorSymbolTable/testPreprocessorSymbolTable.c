/*
Test Modulo Symbol Table
Pruebas de las funciones del modulo Symbol Table
Grupo Nro 3 del curso K2051 Lunes TN
20210914
*/
#include "preprocessorSymbolTable.h"
#include "string.h"
#include <assert.h>

int main()
{
    printf("\nComienzo de test del modulo symbolTable\n");

    //Test de la funcion set
    //Cargo palabras reservadas
    assert(setPrep("define",idReservado) == idReservado);
    assert(setPrep("undef",idReservado) == idReservado);
    assert(setPrep("ifdef",idReservado) == idReservado);
    assert(setPrep("endif",idReservado) == idReservado);
    assert(setPrep("include",idReservado) == idReservado);

    //Cargo id's de defines
    assert(setPrep("UNO",idDefine) == idDefine);
    assert(setPrep("DOS",idDefine) == idDefine);
    assert(setPrep("TRES",idDefine) == idDefine);

    //Cargo id's comunes
    assert(setPrep("nombre",idComun) == idComun);
    assert(setPrep("apellido",idComun) == idComun);
    assert(setPrep("telefono",idComun) == idComun);
    assert(setPrep("int",idComun) == idComun);


    //Test de la funcion "get"
    assert(getPrep("define") == idReservado);
    assert(getPrep("nombre") != idReservado);

    assert(getPrep("UNO") == idDefine);
    assert(getPrep("include") != idDefine);
    assert(getPrep("telefono") == idComun);
    assert(getPrep("DOS") != idComun);
    assert(getPrep("char") == Error);
    assert(getPrep("nombre") != Error);
    assert(getPrep("direccion") == Error);
    assert(getPrep("int") != Error);


    //Test de la funcion "delete"
    assert(deletePrep("char") == 0);
    assert(deletePrep("nombre") == 1);
    assert(deletePrep("direccion") == 0);
    assert(deletePrep("int") == 1);
    assert(deletePrep("define") == 1);
    assert(deletePrep("UNO") == 1);
    assert(deletePrep("telefono") == 1);
    
    assert(deletePrep("DOS") == 1);
    assert(deletePrep("apellido") == 1);
    assert(deletePrep("endif") == 1);

    assert(getPrep("UNO") == Error);
    assert(getPrep("maxi") == Error);

    //Prueba global
    assert(setPrep("CINCO",idDefine) == idDefine);
    assert(getPrep("CINCO") == idDefine);
    assert(deletePrep("CINCO") == 1);
    assert(getPrep("CINCO") == Error);
    assert(deletePrep("CINCO") == 0);
    assert(setPrep("CINCO",idComun) == idComun);
    assert(getPrep("CINCO") == idComun);
    assert(deletePrep("CINCO") == 1);
    assert(getPrep("CINCO") == Error);
    assert(deletePrep("CINCO") == 0);

    
    printf("\nLos test se ejecutaron correctamente\n\n");
}
