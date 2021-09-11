#ifndef LOOKUPTABLE_H_INCLUDED
#define LOOKUPTABLE_H_INCLUDED

#define HASHSIZE 101

struct nlist  
{
    struct nlist *siguiente; /* siguiente entrada en la cadena */
    char *identificador; /* identificador */
    char *define; /* texto de reemplazo */
}; /* entrada de la tabla: */

static struct nlist *hashtab[HASHSIZE]; /* tabla de apuntadores*/

//Funciones
const char *set(char*, char*);
const char *get(char*);
const char *delete(char*);

#endif
