//#ifndef LOOKUPTABLE_H_INCLUDED2
//#define LOOKUPTABLE_H_INCLUDED

#include <stdio.h>

#define HASHSIZE 101

struct nlist2  
{
    struct nlist2 *siguiente; /* siguiente entrada en la cadena */
    char *identificador; /* identificador */
    char *define; /* texto de reemplazo */
}; /* entrada de la tabla: */

static struct nlist2 *defineHashtab[HASHSIZE]; /* tabla de apuntadores*/

//Funciones
const char *set(char*, char*);
const char *get(char*);
int delete(char*);

//#endif
