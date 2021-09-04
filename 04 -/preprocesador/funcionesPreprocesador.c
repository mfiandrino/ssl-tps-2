#include "funcionesPreprocesador.h"

static void comentarioFinDeLinea(int);
static void comentarioMultilinea(int);
static void posibleFinDeComentarioMultilinea(int);
static void FinDeComentarioMultilinea(int);
static void posibleComentario(int);
static void caracterComun(int);
static void comienzoDeLinea(int);
static void aperturaComillasSimples(int);
static void entreComillasSimples(int);
static void cierreComillasSimples(int);
static void aperturaComillasDobles(int);
static void cierreComillasDobles(int);
static void entreComillasDobles(int);



int preprocesador()
{
    int c;
    fun_ptr = &comienzoDeLinea;
    while ((c=getchar( ))!= EOF) 
    {
        (*fun_ptr)(c);
    }
}

static void comentarioFinDeLinea(int c) //Dentro de un comentario de linea
{
    switch (c)
    {
        case '\n':
            putchar(' ');
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        default: //EOC
            fun_ptr = &comentarioFinDeLinea;
    }
}

static void comentarioMultilinea(int c) //Dentro de comentario multilinea
{
    switch (c)
    {
        case '*':
            fun_ptr = &posibleFinDeComentarioMultilinea;
            break;

        default: //EOC
            fun_ptr = &comentarioMultilinea;
    }
}

static void posibleFinDeComentarioMultilinea(int c) //Dentro de comentario multilinea, posible fin del mismo
{
    switch (c)
    {
        case '*':
            fun_ptr = &posibleFinDeComentarioMultilinea;
            break;

        case '/':
            putchar(' ');
            fun_ptr = &FinDeComentarioMultilinea;
            break;

        default: //EOC
            fun_ptr = &comentarioMultilinea;
    }
}

static void FinDeComentarioMultilinea(int c) //Fin de comentario multilinea, siguiente caracter
{
    switch (c)
    {
        case '/':
            fun_ptr = &posibleComentario;
            break;

        case '\'':
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        default: //EOC
            fun_ptr = &caracterComun;
    }
}

static void posibleComentario(int c) //Llego una / vemos siguiente caracter
{
    switch (c)
    {
        case '\n':
            putchar('/');
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            fun_ptr = &comentarioFinDeLinea;
            break;

        case '\'':
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '*':
            fun_ptr = &comentarioMultilinea;
            break;

        default: //EOC
            putchar('/');
            putchar(c);
            fun_ptr = &caracterComun;
    }
}

static void caracterComun(int c) //Caracter comun
{
    switch (c)
    {
        case '\n':
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '\'':
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '/':
            fun_ptr = &posibleComentario;
            break;

        default: //EOC
        putchar(c);
            fun_ptr = &caracterComun;
    }
}

static void comienzoDeLinea(int c) //Despues de un \n o al principio del archivo
{
    switch (c)
    {
        case '\n':
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            fun_ptr = &posibleComentario;
            break;

        case '\'':
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &caracterComun;
    }
}

static void aperturaComillasSimples(int c) //Apertura comillas simples
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = &cierreComillasSimples;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &entreComillasSimples;
    }
}

static void entreComillasSimples(int c) //Dentro de comillas simples
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = &cierreComillasSimples;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &entreComillasSimples;
    }
}

static void cierreComillasSimples(int c) //Cierre de comillas simples
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            fun_ptr = &posibleComentario;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &caracterComun;
    }
}

static void aperturaComillasDobles(int c)
{
    switch (c)
    {
        case '\"':
            putchar(c);
            fun_ptr = &cierreComillasDobles;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &entreComillasDobles;
    }
}

static void cierreComillasDobles(int c)
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            fun_ptr = &posibleComentario;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &caracterComun;
    }

}

static void entreComillasDobles(int c)
{
    switch (c)
    {
        case '\"':
            putchar(c);
            fun_ptr = &cierreComillasDobles;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &entreComillasDobles;
    }
}
