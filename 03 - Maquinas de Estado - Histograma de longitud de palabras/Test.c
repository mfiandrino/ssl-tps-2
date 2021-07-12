/*
Programa de pruebas
Programa para probar que los histogramas funcionen correctamente, completando un array de contadores inicializados en cero
Grupo Nro 3 del curso K2051 Lunes TN
20210712
*/
#include <assert.h>
#include <stdio.h>

#include "histograma.h"
#include "Graficador.h"

int  main(void)
{
    unsigned int contadores1[largoMaxPalabra+1] = {0};
    printf("\n--------TEST DE HISTOGRAMA 1--------\n\n");
    printf("Escriba \"Programa de prueba para el histograma 1\" y luego presione la combinacion de teclas para dejar de ingresar datos\n");
    implementarHistograma("1",contadores1,largoMaxPalabra+1);

    assert(contadores1[1] == 1);
    assert(contadores1[2] == 2);
    assert(contadores1[3] == 0);
    assert(contadores1[4] == 1);
    assert(contadores1[5] == 0);
    assert(contadores1[6] == 1);
    assert(contadores1[7] == 0);
    assert(contadores1[8] == 1);
    assert(contadores1[9] == 0);
    assert(contadores1[10] == 1);
    assert(contadores1[11] == 0);
    assert(contadores1[4] != 2);
    assert(contadores1[5] != 4);
    assert(contadores1[6] != 0);
    assert(contadores1[7] != -1);

    printf("\nLa prueba del histograma 1 finalizó con éxito\n");
    
    graficarHistograma('/',contadores1,largoMaxPalabra+1);

    clearerr(stdin);
//-----------------------------------------------------------------------------

    unsigned int contadores2[largoMaxPalabra+1] = {0};
    printf("\n--------TEST DE HISTOGRAMA 2--------\n\n");
    printf("Escriba \"Este es el programa de prueba para la implementacion del segundo histograma\" y luego presione la combinacion de teclas para dejar de ingresar datos\n");
    implementarHistograma("2",contadores2,largoMaxPalabra+1);

    assert(contadores2[1] == 0);
    assert(contadores2[2] == 4);
    assert(contadores2[3] == 1);
    assert(contadores2[4] == 2);
    assert(contadores2[5] == 0);
    assert(contadores2[6] == 1);
    assert(contadores2[7] == 1);
    assert(contadores2[8] == 1);
    assert(contadores2[9] == 0);
    assert(contadores2[10] == 1);
    assert(contadores2[11] == 0);
    assert(contadores2[12] == 0);
    assert(contadores2[13] == 0);
    assert(contadores2[14] == 1);
    assert(contadores2[15] == 0);
    assert(contadores2[2] != 1);
    assert(contadores2[3] != -4);
    assert(contadores2[4] != 8);

    printf("\nLa prueba del histograma 2 finalizó con éxito\n");

    graficarHistograma('/',contadores2,largoMaxPalabra+1);    

    clearerr(stdin);
//-----------------------------------------------------------------------------

    unsigned int contadores3[largoMaxPalabra+1] = {0};
    printf("\n--------TEST DE HISTOGRAMA 3--------\n\n");
    printf("Escriba \"Con este programa(tecla enter)\nvamos a probar el histograma 3\" y luego presione la combinacion de teclas para dejar de ingresar datos\n");
    implementarHistograma("3",contadores3,largoMaxPalabra+1);


    assert(contadores3[1] == 2);
    assert(contadores3[2] == 1);
    assert(contadores3[3] == 1);
    assert(contadores3[4] == 1);
    assert(contadores3[5] == 1);
    assert(contadores3[6] == 1);
    assert(contadores3[7] == 0);
    assert(contadores3[8] == 1);
    assert(contadores3[9] == 0);
    assert(contadores3[10] == 1);
    assert(contadores3[11] == 0);
    assert(contadores3[9] != 4);
    assert(contadores3[10] != 0);
    assert(contadores3[11] != 2);

    printf("\nLa prueba del histograma 3 finalizó con éxito\n");

    graficarHistograma('/',contadores3,largoMaxPalabra+1);    

    clearerr(stdin);
//-----------------------------------------------------------------------------

    unsigned int contadores4[largoMaxPalabra+1] = {0};
    printf("\n--------TEST DE HISTOGRAMA 4--------\n\n");
    printf("Escriba \"Hemos hecho este test para probar los histogramas(tecla enter)\nEn este caso sera el histograma numero 4\" y luego presione la combinacion de teclas para dejar de ingresar datos\n");
    implementarHistograma("4",contadores4,largoMaxPalabra+1);


    assert(contadores4[1] == 1);
    assert(contadores4[2] == 2);
    assert(contadores4[3] == 1);
    assert(contadores4[4] == 6);
    assert(contadores4[5] == 2);
    assert(contadores4[6] == 2);
    assert(contadores4[7] == 0);
    assert(contadores4[8] == 0);
    assert(contadores4[9] == 0);
    assert(contadores4[10] == 1);
    assert(contadores4[11] == 1);
    assert(contadores4[6] != 3);
    assert(contadores4[7] != 1);
    assert(contadores4[8] != -3);

    
    printf("\nLa prueba del histograma 4 finalizó con éxito\n");

    graficarHistograma('/',contadores4,largoMaxPalabra+1);    

    clearerr(stdin);
//-----------------------------------------------------------------------------

return 0;
}