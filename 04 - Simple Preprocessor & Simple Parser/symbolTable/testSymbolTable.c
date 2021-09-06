#include "symbolTable.h"
#include <stdio.h>

void imprimirElemento(char *id)
{
    struct nlist *elemento;
    if((elemento = lookup(id)) == NULL)
        printf("\nEl elemento \"%s\" no esta en la tabla",id);
    else    
        printf("\nEl define es: %s",elemento->define);
}

int main()
{
    char texto[30];
    memset(texto,'\0',sizeof(char) * 30);
    texto[0] = 'M';
    texto[1] = 'A';
    texto[2] = 'X';
    texto[3] = 'I';
    texto[4] = 'M';
    texto[5] = 'O';
    install(texto,"155");
    install("UNO","1");
    install("DOS","2");
    install("TRES","3");
    install("CUATRO","4");
    install("CINCO","5");
    install("SEIS","6");
    install("SIETE","7");
    install("OCHO","8");
    install("NUEVE","9");
    imprimirElemento(texto);
    imprimirElemento("MINIMO");
    undef(texto);
    imprimirElemento(texto);

    imprimirElemento("UNO");
    imprimirElemento("DOS");
    imprimirElemento("TRES");
    imprimirElemento("CUATRO");
    undef("CUATRO");
    imprimirElemento("CUATRO");
    install("CUATRO","444");
    install("DIEZ","10");
    install("ONCE","11");
    imprimirElemento("CINCO");
    imprimirElemento("SEIS");
    imprimirElemento("SIETE");
    imprimirElemento("OCHO");
    imprimirElemento("CUATRO");
    imprimirElemento("NUEVE");
    imprimirElemento("DIEZ");
    imprimirElemento("ONCE");

    
}