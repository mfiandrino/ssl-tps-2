/*
Funciones auxiliares para el Main
Funciones para validar si la implemetacion ingresada por consola es válida y para implemetar un histograma en específico
Grupo Nro 3 del curso K2051 Lunes TN
20210712
*/
#include "histograma.h"

int *implementarHistograma(char *implementacion, unsigned int* contadores, unsigned int cantContadores)
{
    if(strcmp(implementacion,"1") == 0)
        histograma1(contadores,cantContadores);

    else if(strcmp(implementacion,"2") == 0)
        histograma2(contadores,cantContadores);

    else if(strcmp(implementacion,"3") == 0)
        histograma3(contadores,cantContadores);
       
    else
        histograma4(contadores,cantContadores);
        
}

int validarHistograma(char *implementacion)
{
    if(strcmp(implementacion,"1") == 0 || strcmp(implementacion,"2") == 0 || strcmp(implementacion,"3") == 0 || strcmp(implementacion,"4") == 0)
        return 1;
    else
    {
        printf("\nIngrese una implementacion valida\n\n");
        return 0;
    }
}

