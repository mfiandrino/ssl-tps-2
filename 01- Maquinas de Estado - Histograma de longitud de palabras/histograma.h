#ifndef HISTOGRAMA_H_INCLUDED
#define HISTOGRAMA_H_INCLUDED
#include <string.h>
#include <stdio.h>

#define largoMaxPalabra 100
//const unsigned int largoMaxPalabra = 100;

int *implementarHistograma(char *,unsigned int*, unsigned int);
int validarHistograma(char *);

void histograma1(unsigned int*, unsigned int); //Histograma con enum y switch

void histograma2(unsigned int*, unsigned int); //Histograma con goto

void histograma3(); //Histograma con recursividad

void histograma4(); //Histograma x

#endif
