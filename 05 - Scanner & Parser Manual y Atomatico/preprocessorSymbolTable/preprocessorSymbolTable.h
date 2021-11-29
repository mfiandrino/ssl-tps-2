#ifndef LOOKUPTABLE_H_INCLUDED
#define LOOKUPTABLE_H_INCLUDED

#include <stdio.h>

#define HASHSIZE 101

typedef enum {
    idReservado,
    idComun,
    idDefine,
    Error
} IdType;

struct nlist  
{
    struct nlist *siguiente; /* siguiente entrada en la cadena */
    char *identificador; /* identificador */
    IdType idType; /* texto de reemplazo */
}; /* entrada de la tabla: */

static struct nlist *hashtab[HASHSIZE]; /* tabla de apuntadores*/

//Funciones
IdType setPrep(char*, IdType);
IdType getPrep(char*);
int deletePrep(char*);

#endif
