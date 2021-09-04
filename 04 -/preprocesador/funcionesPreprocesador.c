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

int preprocesador()
{
    int c;
    fun_ptr = &comienzoDeLinea;
    while ((c=getchar( ))!= EOF) 
    {
        (*fun_ptr)(c);
    }
}

static void comentarioFinDeLinea(int c)
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

static void comentarioMultilinea(int c)
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

static void posibleFinDeComentarioMultilinea(int c)
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

static void FinDeComentarioMultilinea(int c)
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

        case '\n':
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        default: //EOC
            fun_ptr = &caracterComun;
    }
}

static void posibleComentario(int c)
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

        case '*':
            fun_ptr = &comentarioMultilinea;
            break;

        default: //EOC
            putchar('/');
            putchar(c);
            fun_ptr = &caracterComun;
    }
}

static void caracterComun(int c)
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

        case '/':
            fun_ptr = &posibleComentario;
            break;

        default: //EOC
        putchar(c);
            fun_ptr = &caracterComun;
    }
}

static void comienzoDeLinea(int c)
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

        default: //EOC
            putchar(c);
            fun_ptr = &caracterComun;
    }
}

static void aperturaComillasSimples(int c)
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

static void entreComillasSimples(int c)
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

static void cierreComillasSimples(int c)
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
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



