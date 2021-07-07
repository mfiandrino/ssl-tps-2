#ifndef HISTOGRAMA_H_INCLUDED
#define HISTOGRAMA_H_INCLUDED
#include <string.h>
#include <stdio.h>

#define largoMaxPalabra 100
//const unsigned int largoMaxPalabra = 100;

int *implementarHistograma(char *,unsigned int*, unsigned int);
int validarHistograma(char *);

unsigned int *histograma1(unsigned int*, unsigned int); //Histograma con enum y switch

unsigned int *histograma2(unsigned int*, unsigned int); //Histograma con goto

unsigned int *histograma3(); //Histograma con recursividad

unsigned int *histograma4(); //Histograma x

#endif
