/*
Funciones Preprocesador
Archivo con la implementacion de las funciones como estados
Grupo Nro 3 del curso K2051 Lunes TN
20210911
*/

#include "funcionesPreprocesador.h"
#include "../symbolTable/symbolTable.h"
#include <stdio.h>
#include <string.h>

#define largoMaxIdentificador 32
int contIdentificador;
char identificador[largoMaxIdentificador];

#define largoMaxTextoDefine 100
int contTextoDefine;
char textoDefine[largoMaxTextoDefine];

#define largoMaxPalabra 100
int contPalabra;
char palabra[largoMaxPalabra];

int (*fun_ptr)(int)= comienzoDeLinea;
const char *elemento;

static int comentarioFinDeLinea(int);
static int comentarioMultilinea(int);
static int posibleFinDeComentarioMultilinea(int);
static int FinDeComentarioMultilinea(int);
static int posibleComentario(int);
static int enPalabra(int);
static int espacio(int);

static int aperturaComillasSimples(int);
static int entreComillasSimples(int);
static int cierreComillasSimples(int);
static int aperturaComillasDobles(int);
static int cierreComillasDobles(int);
static int entreComillasDobles(int);
static int posibleIncludeDefineUndef(int);
static int d(int);
static int de(int);
static int def(int);
static int defi(int);
static int defin(int);
static int define(int);
static int defineEspacio(int);
static int defineIdentificador(int);
static int identificadorInvalido(int);
static int numeralIncorrecto(int);
static int defineIdentificadorEspacio(int);
static int textoDefineInvalido(int);
static int defineTexto(int);
static int u(int);
static int un(int);
static int und(int);
static int unde(int);
static int esUndef(int);
static int undefEspacio(int);
static int undefIdentificador(int);
static int caracterEspecial(int);
static void nuevaPalabra(int);
static void nuevoCaracterEnPalabra(int);
static void nueintentificador(int);
static void nuevoCaracterIdentificador(int);
static void nuevoTextoDefine(int);
static void nuevoCaracterTextoDefine(int);
static void verificarEnTabla();


static int comentarioFinDeLinea(int c) //Dentro de un comentario de linea
{
    switch (c)
    {
        case '\n':
            putchar(' ');
            putchar(c);
            fun_ptr = comienzoDeLinea;
            break;

        default: //EOC
            fun_ptr = comentarioFinDeLinea;
    }
    return 1;
}

static int comentarioMultilinea(int c) //Dentro de comentario multilinea
{
    switch (c)
    {
        case '*':
            fun_ptr = posibleFinDeComentarioMultilinea;
            break;

        default: //EOC
            fun_ptr = comentarioMultilinea;
    }
    return 1;
}

static int posibleFinDeComentarioMultilinea(int c) //Dentro de comentario multilinea, posible fin del mismo
{
    switch (c)
    {
        case '*':
            fun_ptr = posibleFinDeComentarioMultilinea;
            break;

        case '/':
            putchar(' ');
            fun_ptr = FinDeComentarioMultilinea;
            break;

        default: //EOC
            fun_ptr = comentarioMultilinea;
    }
    return 1;
}

static int FinDeComentarioMultilinea(int c) //Fin de comentario multilinea, siguiente caracter
{
    switch (c)
    {
        case '/':
            fun_ptr = posibleComentario;
            break;

        case '\'':
            putchar(c);
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = aperturaComillasDobles;
            break;

        case '\n':
            putchar(c);
            fun_ptr = comienzoDeLinea;
            break;

        case ' ': case '\t':
            putchar(c);
            fun_ptr = espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = caracterEspecial;
    }
    return 1;
}

static int posibleComentario(int c) //Llego una / vemos siguiente caracter
{
    switch (c)
    {
        case '\n':
            putchar('/');
            putchar(c);
            fun_ptr = comienzoDeLinea;
            break;

        case '/':
            fun_ptr = comentarioFinDeLinea;
            break;

        case '\'':
            putchar('/');
            putchar(c);
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            putchar('/');
            putchar(c);
            fun_ptr = aperturaComillasDobles;
            break;

        case '*':
            fun_ptr = comentarioMultilinea;
            break;

        case ' ': case '\t':
            putchar('/');
            putchar(c);
            fun_ptr = espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            putchar('/');
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar('/');
            putchar(c);
            fun_ptr = caracterEspecial;
    }
    return 1;
}

static void verificarEnTabla( ){ 
    if(elemento = get(palabra))
        printf("%s",elemento);
    else
        printf("%s",palabra);
}

static void nuevoCaracterEnPalabra(int c){
    contPalabra++;
    palabra[contPalabra] = c;
}


static int enPalabra(int c) //Caracteres aptos para un identificador
{
    switch (c)
    {
        case '\n':
            verificarEnTabla();        
            putchar(c);
            fun_ptr = comienzoDeLinea;
            break;

        case '\'':
            verificarEnTabla( );
            putchar(c);
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            verificarEnTabla();
            putchar(c);
            fun_ptr = aperturaComillasDobles;
            break;

        case '/':
            verificarEnTabla( );
            fun_ptr = posibleComentario;
            break;

        case ' ': case '\t':
            verificarEnTabla( );
            putchar(c);
            fun_ptr = espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            nuevoCaracterEnPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            verificarEnTabla( );
            putchar(c);
            fun_ptr = caracterEspecial;
            break;
    }
    return 1;
}

static int espacio(int c) //Caracter comun
{
    switch (c)
    {
        case '\n':
            putchar(c);
            fun_ptr = comienzoDeLinea;
            break;

        case '\'':
            putchar(c);
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = aperturaComillasDobles;
            break;

        case '/':
            fun_ptr = posibleComentario;
            break;

        case ' ': case '\t':
            putchar(c);
            fun_ptr = espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = caracterEspecial;
    }
    return 1;
}

static void nuevaPalabra(int c){
    contPalabra = 0;
    memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
    palabra[contPalabra] = c;    
}

static int caracterEspecial(int c) //Caracter especial (distintos a los que puede ser un indentificador)
{
    switch (c)
    {
        case '\n':
            putchar(c);
            fun_ptr = comienzoDeLinea;
            break;

        case '\'':
            putchar(c);
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = aperturaComillasDobles;
            break;

        case '/':
            fun_ptr = posibleComentario;
            break;

        case ' ': case '\t':
            putchar(c);
            fun_ptr = espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = caracterEspecial;       
    }
    return 1;
}

int comienzoDeLinea(int c) //Despues de un \n o al principio del archivo
{
    switch (c)
    {
        case '\n':
            putchar(c);
            fun_ptr = comienzoDeLinea;
            break;

        case '/':
            fun_ptr = posibleComentario;
            break;

        case '#':
            fun_ptr = posibleIncludeDefineUndef;
            break;

        case '\'':
            putchar(c);
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = aperturaComillasDobles;
            break;

        case ' ': case '\t':
            putchar(c);
            fun_ptr = espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
           nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = caracterEspecial;
    }
    return 1;
}

static int aperturaComillasSimples(int c) //Apertura comillas simples
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = cierreComillasSimples;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = entreComillasSimples;
    }
    return 1;
}

static int entreComillasSimples(int c) //Dentro de comillas simples
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = cierreComillasSimples;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = entreComillasSimples;
    }
    return 1;
}

static int cierreComillasSimples(int c) //Cierre de comillas simples
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = aperturaComillasDobles;
            break;

        case '\n':
            putchar(c);
            fun_ptr = comienzoDeLinea;
            break;

        case '/':
            fun_ptr = posibleComentario;
            break;

        case ' ': case '\t':
            putchar(c);
            fun_ptr = espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = caracterEspecial;
    }
    return 1;
}

static int aperturaComillasDobles(int c) //Entramos a las comillas dobles caracteres adentro
{
    switch (c)
    {
        case '\"':
            putchar(c);
            fun_ptr = cierreComillasDobles;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = entreComillasDobles;
    }
    return 1;
}

static int cierreComillasDobles(int c) //Cierre de comillas dobles, se busca el siguiente caracter
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = aperturaComillasDobles;
            break;

        case '\n':
            putchar(c);
            fun_ptr = comienzoDeLinea;
            break;

        case '/':
            fun_ptr = posibleComentario;
            break;

        case ' ': case '\t':
            putchar(c);
            fun_ptr = espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = caracterEspecial;
    }
    return 1;
}

static int entreComillasDobles(int c) //Entre comillas dobles, se buscan los caracteres adentro de las
{
    switch (c)
    {
        case '\"':
            putchar(c);
            fun_ptr = cierreComillasDobles;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = entreComillasDobles;
    }
    return 1;
}

static int posibleIncludeDefineUndef(int c) //Tengo un # Busco una 'd' 'u' 'i'
{
    switch (c)
    {
        case 'd':
            fun_ptr = d;
            break;

        case 'u':
            fun_ptr = u;
            break;
        
        case 'i':
            putchar('#');
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int d(int c) // Encuentro una 'd' buscamos completar el define
{
    switch (c)
    {
        case 'e':
            fun_ptr = de;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int de(int c) // Encuentro una 'de' buscamos completar el define
{
    switch (c)
    {
        case 'f':
            fun_ptr = def;
            break;

        default: //EOC 
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int def(int c) // Encuentro una 'def' buscamos completar el define
{
    switch (c)
    {
        case 'i':
            fun_ptr = defi;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int defi(int c) // Encuentro una 'defi' buscamos completar el define
{
    switch (c)
    {
        case 'n':
            fun_ptr = defin;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int defin(int c) // Encuentro una 'defin' buscamos completar el define
{
    switch (c)
    {
        case 'e':
            fun_ptr = define;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int define(int c) // Encuentro una 'define' buscamos espacio para el identificador
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = defineEspacio;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static void nuevoIdentificador(int c){
    contIdentificador = 0;
    memset(identificador,'\0',sizeof(char) * largoMaxIdentificador);
    identificador[contIdentificador] = c;
}

static int defineEspacio(int c) // Espacio en el define, llenamos la palabra del identificador
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z':
            nuevoIdentificador(c);
            fun_ptr = defineIdentificador;
            break;

        case ' ': case '\t':
            fun_ptr = defineEspacio;
            break;

        default: //EOC
            fun_ptr = identificadorInvalido;
    }
    return 1;
}

static void nuevoCaracterIdentificador(int c){
    contIdentificador++;
    identificador[contIdentificador] = c;
}

static int defineIdentificador(int c) // Identificador completo del define
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            nuevoCaracterIdentificador(c);
            fun_ptr = defineIdentificador;
            break;

        case ' ': case '\t':
            fun_ptr = defineIdentificadorEspacio;
            break;

        default: //EOC
            fun_ptr = identificadorInvalido;
    }
    return 1;
}

static int identificadorInvalido(int c) //Identificador invalido
{
    return -1;
}

static int numeralIncorrecto(int c)
{
    return -3;
}

static void nuevoTextoDefine(int c){
    contTextoDefine = 0;
    memset(textoDefine,'\0',sizeof(char) * largoMaxTextoDefine);
    textoDefine[contTextoDefine] = c;
}

static int defineIdentificadorEspacio(int c) //Buscamos el texto a reemplazar del idenficador
{
    switch (c)
    {
        case '\n':
            fun_ptr = textoDefineInvalido;
            break;

        case ' ': case '\t':
            fun_ptr = defineIdentificadorEspacio;
            break;

        default: //EOC
            nuevoTextoDefine(c);
            fun_ptr = defineTexto;
    }
    return 1;
}

static int textoDefineInvalido(int c) //Texto invalido
{
    return -2;
}

static void nuevoCaracterTextoDefine(int c){
    contTextoDefine++;
    textoDefine[contTextoDefine] = c;
}


static int defineTexto(int c) //Texto correspondiente al identificador
{
    switch (c)
    {
        case '\n':
            set(identificador,textoDefine);
            fun_ptr = comienzoDeLinea;
            break;

        default: //EOC
            nuevoCaracterTextoDefine(c);
            fun_ptr = defineTexto;
    }
    return 1;
}

static int u(int c) // Encuentro una 'u' buscamos completar el undef
{
    switch (c)
    {
        case 'n':
            fun_ptr = un;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int un(int c)  // Encuentro una 'un' buscamos completar el undef
{
    switch (c)
    {
        case 'd':
            fun_ptr = und;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int und(int c)  // Encuentro una 'und' buscamos completar el undef
{
    switch (c)
    {
        case 'e':
            fun_ptr = unde;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int unde(int c)  // Encuentro una 'unde' buscamos completar el undef
{
    switch (c)
    {
        case 'f':
            fun_ptr = esUndef;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}

static int esUndef(int c)  // Encuentro un 'undef'
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = undefEspacio;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
    return 1;
}


static int undefEspacio(int c) //Espacio despues del undef, busco el identificador asociado
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z':
            nuevoIdentificador(c);
            fun_ptr = undefIdentificador;
            break;

        case ' ': case '\t':
            fun_ptr = undefEspacio;
            break;

        default: //EOC
            fun_ptr = identificadorInvalido;
    }
    return 1;
}

static int undefIdentificador(int c) //Identificador asociado al undef, se deja de asociar para el cambio
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
           nuevoCaracterIdentificador(c);
            fun_ptr = undefIdentificador;
            break;

        case '\n' :
            delete(identificador);
            fun_ptr = comienzoDeLinea;
            break;

        default: //EOC
            fun_ptr = identificadorInvalido;
    }  
    return 1; 
}






