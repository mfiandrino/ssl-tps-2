/*
Modulo Symbol Table
Implementación de las funciones para guardar, buscar y borrar datos de una tabla de simbolos
Grupo Nro 3 del curso K2051 Lunes TN
20210914
*/

#include "preprocessorSymbolTable.h"
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
IdType getPrep(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->siguiente)
    {
        if (strcmp(s, np->identificador) == 0)
        {
            return np->idType; /* se encontró */
        }
    }
    return Error;  /* no se encontró */
}

/* getStruct: busca s en hashtab y devuelve la estructura */
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
IdType setPrep(char *identificador, IdType idType1)
{
    char *strdup (const char*);
    struct nlist *np;
    unsigned hashval;

    if ((np = getStruct(identificador)) == NULL)  /* no fue encontrado */
    {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->identificador = strdup(identificador)) == NULL)
            return Error;
        hashval = hash(identificador);
        np->siguiente = hashtab[hashval];
        hashtab[hashval] = np;
    } 
    else /* ya está allí */
        free((void *) np->idType); /* libera la anterior define */

    if ((np->idType = idType1) == Error)
        return Error;

    return np->idType;
}

/* delete: borra identificador dentro de hashtab y devuelve 1 en caso de exito, o 0 en caso contrario*/
int deletePrep(char * identificador)
{
    struct nlist *np1, *np2;

    if((np1 = getStruct(identificador)) == NULL) //No encontro el identificador
        return 0;

    for (np1 = np2 = hashtab[hash(identificador)]; np1 != NULL;np2 = np1, np1 = np1->siguiente) 
    {
        if(strcmp(identificador, np1->identificador) == 0 ) //Encontro el identificador
        {
        //  Remuevo el nodo de la lista 
        if ( np1 == np2 )
            hashtab[hash(identificador)] = np1->siguiente;
        else
            np2->siguiente = np1->siguiente;

        // Libero la memoria dinamica 
        free(np1->identificador);
        free(np1);
        return 1;
        }
    }
    return 0;  //No encontro el identificador
}

