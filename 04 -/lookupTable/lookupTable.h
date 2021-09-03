#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist  
{
    struct nlist *siguiente; /* siguiente entrada en la cadena */
    char *identificador; /* identificador */
    char *define; /* texto de reemplazo */
}; /* entrada de la tabla: */

static struct nlist *hashtab[HASHSIZE]; /* tabla de apuntadores*/

//Funciones
struct nlist *install(char*, char*);
struct nlist *lookup(char*);
struct nlist *undef(char*);