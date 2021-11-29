/*
Modulo Symbol Table para #define
Implementación de las funciones para guardar, buscar y borrar datos de una tabla de simbolos para atender a #define
Grupo Nro 3 del curso K2051 Lunes TN
20211104
*/

#include "defineSymbolTable.h"
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
    struct nlist2 *np;
    for (np = defineHashtab[hash(s)]; np != NULL; np = np->siguiente)
    {
        if (strcmp(s, np->identificador) == 0)
        {
            return np->define; /* se encontró */
        }
    }
    return NULL;  /* no se encontró */
}

/* get2: busca s en hashtab y devuelve la estructura */
static struct nlist2 *getStruct(char *s)
{
    struct nlist2 *np;
    for (np = defineHashtab[hash(s)]; np != NULL; np = np->siguiente)
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
    struct nlist2 *np;
    unsigned hashval;

    if ((np = getStruct(identificador)) == NULL)  /* no fue encontrado */
    {
        np = (struct nlist2 *) malloc(sizeof(*np));
        if (np == NULL || (np->identificador = strdup(identificador)) == NULL)
            return NULL;
        hashval = hash(identificador);
        np->siguiente = defineHashtab[hashval];
        defineHashtab[hashval] = np;
    } 
    else /* ya está allí */
        free((void *) np->define); /* libera la anterior define */

    if ((np->define = strdup(define)) == NULL)
        return NULL;

    return np->define;
}

/* delete: borra identificador dentro de hashtab y devuelve 1 en caso de exito, o 0 en caso contrario*/
int delete(char * identificador)
{
    struct nlist2 *np1, *np2;

    if((np1 = getStruct(identificador)) == NULL) //No encontro el identificador
        return 0;

    for (np1 = np2 = defineHashtab[hash(identificador)]; np1 != NULL;np2 = np1, np1 = np1->siguiente) 
    {
        if(strcmp(identificador, np1->identificador) == 0 ) //Encontro el identificador
        {
        //  Remuevo el nodo de la lista 
        if ( np1 == np2 )
            defineHashtab[hash(identificador)] = np1->siguiente;
        else
            np2->siguiente = np1->siguiente;

        // Libero la memoria dinamica 
        free(np1->identificador);
        free(np1->define);
        free(np1);
        return 1;
        }
    }
    return 0;  //No encontro el identificador
}
