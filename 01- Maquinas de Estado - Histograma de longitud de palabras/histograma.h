#ifndef HISTOGRAMA_H_INCLUDED
#define HISTOGRAMA_H_INCLUDED
#include <string.h>
#include <stdio.h>

#define largoMaxPalabra 100

int *implementarHistograma(char *);
int validarHistograma(char *);

unsigned int *histograma1(); //Histograma con enum y switch

unsigned int *histograma2(); //Histograma con goto

unsigned int *histograma3(); //Histograma con recursividad

unsigned int *histograma4(); //Histograma x

#endif
