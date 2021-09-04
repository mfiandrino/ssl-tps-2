#include "lookupTable.h"
#include <stdio.h>

/* hash: forma un valor hash para la cadena s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

/* lookup: busca s en hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->siguiente)
    {
        if (strcmp(s, np->identificador) == 0)
        {
            return np; /* se encontró */
        }
    }
    return NULL;  /* no se encontró */
}

/* install: coloca (identificador, define) dentro de hashtab */
struct nlist *install(char *identificador, char *define)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(identificador)) == NULL)  /* no fue encontrado */
    {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->identificador = strdup(identificador)) == NULL)
            return NULL;
        hashval = hash(identificador);
        np->siguiente = hashtab[hashval];
        hashtab[hashval] = np;
    } 
    else /* ya está allí */
        free((void *) np->define); /* libera la anterior define */

    if ((np->define = strdup(define)) == NULL)
        return NULL;

    return np;
}

struct nlist *undef(char *identificador) 
{
    struct nlist *found = lookup(identificador);

    if (found == NULL) /* no se encontro */
        return NULL;
    else 
    {
        if (found->siguiente != NULL) 
        {
            found->siguiente = found->siguiente->siguiente;
            found = found->siguiente;
        }
        else 
        {
            hashtab[hash(identificador)] = NULL;
            free((void *) found);
        }
    }
    return found;
}

