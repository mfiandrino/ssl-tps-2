/*
Modulo Symbol Table
Implementación de las funciones para guardar, buscar y borrar datos de una tabla de simbolos
Grupo Nro 3 del curso K2051 Lunes TN
20210911
*/
#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* hash: forma un valor hash para la cadena s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

/* get: busca s en hashtab y devuelve el texto a reemplazar*/
const char *get(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->siguiente)
    {
        if (strcmp(s, np->identificador) == 0)
        {
            return np->define; /* se encontró */
        }
    }
    return NULL;  /* no se encontró */
}

/* get2: busca s en hashtab y devuelve la estructura */
static struct nlist *getStruct(char *s)
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

/* set: coloca (identificador, define) dentro de hashtab y devuelve el texto a reemplazar*/
const char *set(char *identificador, char *define)
{
    char *strdup (const char*);
    struct nlist *np;
    unsigned hashval;

    if ((np = getStruct(identificador)) == NULL)  /* no fue encontrado */
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

    return np->define;
}

/* delete: borra identificador dentro de hashtab y devuelve el texto a reemplazar*/
const char *delete(char *identificador) 
{
    struct nlist *found = getStruct(identificador);

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
    return found->define;
}

