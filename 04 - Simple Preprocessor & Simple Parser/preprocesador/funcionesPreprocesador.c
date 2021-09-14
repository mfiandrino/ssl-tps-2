/*
Funciones Preprocesador
Archivo con la implementacion de las funciones como estados
Grupo Nro 3 del curso K2051 Lunes TN
20210914
*/

#include "funcionesPreprocesador.h"
#include "../symbolTable/symbolTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    NUMERAL_INCORRECTO,
    TEXTO_DEFINE_INVALIDO,
    IDENTIFICADOR_INVALIDO,
    PATH_INVALIDO,
    ARCHIVO_INEXISTENTE
}error;

#define largoMaxIdentificador 32
int contIdentificador;
char identificador[largoMaxIdentificador];

#define largoMaxTextoDefine 100
int contTextoDefine;
char textoDefine[largoMaxTextoDefine];

#define largoMaxPalabra 100
int contPalabra;
char palabra[largoMaxPalabra];

#define largoMaxPath 100
int contPath;
char path[largoMaxPath];

//--------------ESTADOS--------------------
/*Comentarios*/
static void posibleComentario(int);
static void comentarioFinDeLinea(int);
static void comentarioMultilinea(int);
static void posibleFinDeComentarioMultilinea(int);

/*Generales*/
static void enPalabra(int);
static void comienzoDeLinea(int);
static void restoDeLinea(int);

/*Comillas*/
static void aperturaComillasSimples(int);
static void entreComillasSimples(int);
static void aperturaComillasDobles(int);
static void entreComillasDobles(int);

/*Define, Undef e Include*/
static void posibleIncludeDefineUndef(int);

static void d(int);
static void de(int);
static void def(int);
static void defi(int);
static void defin(int);
static void define(int);
static void defineEspacio(int);
static void defineIdentificador(int);
static void defineIdentificadorEspacio(int);
static void defineTexto(int);

static void u(int);
static void un(int);
static void und(int);
static void unde(int);
static void esUndef(int);
static void undefEspacio(int);
static void undefIdentificador(int);

static void i(int);
static void in(int);
static void inc(int);
static void incl(int);
static void inclu(int);
static void includ(int);
static void include(int);
static void includeComillas(int);
static void includePath(int);

/*Errores*/
static void textoDefineInvalido(int);
static void identificadorInvalido(int);
static void numeralIncorrecto(int);
static void pathInvalido(int);
//--------------FIN ESTADOS-----------------


/*Funciones varias*/
static void traerArchivoInclude();
static void verificarEnTabla();
static void manejoDeErrores(error);

static void nuevoTextoDefine(int);
static void nuevoCaracterTextoDefine(int);
static void nuevoPath(int);
static void nuevoCaracterPath(int);
static void nuevaPalabra(int);
static void nuevoCaracterEnPalabra(int);
static void nuevoIdentificador(int);
static void nuevoCaracterIdentificador(int);

//Asignacion de estado inicial
void (*fun_ptr)(int)= comienzoDeLinea;

static void comentarioFinDeLinea(int c) //Dentro de un comentario de linea
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
}

static void comentarioMultilinea(int c) //Dentro de comentario multilinea
{
    switch (c)
    {
        case '*':
            fun_ptr = posibleFinDeComentarioMultilinea;
            break;

        default: //EOC
            fun_ptr = comentarioMultilinea;
    }
}

static void posibleFinDeComentarioMultilinea(int c) //Dentro de comentario multilinea, posible fin del mismo
{
    switch (c)
    {
        case '*':
            fun_ptr = posibleFinDeComentarioMultilinea;
            break;

        case '/':
            putchar(' ');
            fun_ptr = restoDeLinea;
            break;

        default: //EOC
            fun_ptr = comentarioMultilinea;
    }
}

static void restoDeLinea(int c) //Fin de comentario multilinea, siguiente caracter
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

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = restoDeLinea;
    }
}

static void posibleComentario(int c) //Llego una / vemos siguiente caracter
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

        case '_': case 'A'...'Z': case 'a'...'z':
            putchar('/');
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar('/');
            putchar(c);
            fun_ptr = restoDeLinea;
    }
}

static void enPalabra(int c) //Caracteres aptos para un identificador
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

        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            nuevoCaracterEnPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            verificarEnTabla( );
            putchar(c);
            fun_ptr = restoDeLinea;
            break;
    }
}

static void comienzoDeLinea(int c) //Despues de un \n o al principio del archivo
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

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = restoDeLinea;
    }
}

static void aperturaComillasSimples(int c) //Apertura comillas simples
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = restoDeLinea;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = entreComillasSimples;
    }
}

static void entreComillasSimples(int c) //Dentro de comillas simples
{
    switch (c)
    {
        case '\'':
            putchar(c);
            fun_ptr = restoDeLinea;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = entreComillasSimples;
    }
}


static void aperturaComillasDobles(int c) //Entramos a las comillas dobles caracteres adentro
{
    switch (c)
    {
        case '\"':
            putchar(c);
            fun_ptr = restoDeLinea;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = entreComillasDobles;
    }
}


static void entreComillasDobles(int c) //Entre comillas dobles, se buscan los caracteres adentro de las
{
    switch (c)
    {
        case '\"':
            putchar(c);
            fun_ptr = restoDeLinea;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = entreComillasDobles;
    }
}

static void posibleIncludeDefineUndef(int c) //Tengo un # Busco una 'd' 'u' 'i'
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
            fun_ptr = i;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void d(int c) // Encuentro una 'd' buscamos completar el define
{
    switch (c)
    {
        case 'e':
            fun_ptr = de;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void de(int c) // Encuentro una 'de' buscamos completar el define
{
    switch (c)
    {
        case 'f':
            fun_ptr = def;
            break;

        default: //EOC 
            fun_ptr = numeralIncorrecto;
    }
}

static void def(int c) // Encuentro una 'def' buscamos completar el define
{
    switch (c)
    {
        case 'i':
            fun_ptr = defi;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void defi(int c) // Encuentro una 'defi' buscamos completar el define
{
    switch (c)
    {
        case 'n':
            fun_ptr = defin;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void defin(int c) // Encuentro una 'defin' buscamos completar el define
{
    switch (c)
    {
        case 'e':
            fun_ptr = define;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void define(int c) // Encuentro una 'define' buscamos espacio para el identificador
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = defineEspacio;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void defineEspacio(int c) // Espacio en el define, llenamos la palabra del identificador
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
}

static void defineIdentificador(int c) // Identificador completo del define
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
}

static void defineIdentificadorEspacio(int c) //Buscamos el texto a reemplazar del idenficador
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
}

static void defineTexto(int c) //Texto correspondiente al identificador
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
}

static void u(int c) // Encuentro una 'u' buscamos completar el undef
{
    switch (c)
    {
        case 'n':
            fun_ptr = un;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void un(int c)  // Encuentro una 'un' buscamos completar el undef
{
    switch (c)
    {
        case 'd':
            fun_ptr = und;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void und(int c)  // Encuentro una 'und' buscamos completar el undef
{
    switch (c)
    {
        case 'e':
            fun_ptr = unde;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void unde(int c)  // Encuentro una 'unde' buscamos completar el undef
{
    switch (c)
    {
        case 'f':
            fun_ptr = esUndef;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void esUndef(int c)  // Encuentro un 'undef'
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = undefEspacio;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}


static void undefEspacio(int c) //Espacio despues del undef, busco el identificador asociado
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
}

static void undefIdentificador(int c) //Identificador asociado al undef, se deja de asociar para el cambio
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
}

static void i(int c) // Encuentro una 'i' buscamos completar el include
{
    switch (c)
    {
        case 'n':
            fun_ptr = in;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void in(int c) // Encuentro una 'in' buscamos completar el include
{
    switch (c)
    {
        case 'c':
            fun_ptr = inc;
            break;

        default: //EOC 
            fun_ptr = numeralIncorrecto;
    }
}

static void inc(int c) //Encuentro una 'inc' buscamos completar el include
{
    switch (c)
    {
        case 'l':
            fun_ptr = incl;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void incl(int c) // Encuentro una 'incl' buscamos completar el include
{
    switch (c)
    {
        case 'u':
            fun_ptr = inclu;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void inclu(int c) // Encuentro una 'inclu' buscamos completar el include
{
    switch (c)
    {
        case 'd':
            fun_ptr = includ;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void includ(int c) // Encuentro una 'includ' buscamos completar el include
{
    switch (c)
    {
        case 'e':
            fun_ptr = include;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void include(int c) // Encuentro un 'include' buscamos espacio para el path
{
    switch (c)
    {
        case '\"': 
            fun_ptr = includeComillas;
            break;

        case ' ': case '\t':
            fun_ptr = include;
            break;

        default: //EOC
            fun_ptr = numeralIncorrecto;
    }
}

static void includeComillas(int c) // Comillas en el include, llenamos la palabra del path
{
    switch (c)
    {
        case '\n':
            fun_ptr = pathInvalido;
            break;

        default: //EOC 
            nuevoPath(c);
            fun_ptr = includePath;
    }
}

static void includePath(int c) // Path completo del include
{
    switch (c)
    {
        case '\"': 
            traerArchivoInclude();
            fun_ptr = restoDeLinea;
            break;

        case '\n':
            fun_ptr = pathInvalido;
            break;

        default: //EOC
            nuevoCaracterPath(c);
            fun_ptr = includePath;
    }
}

static void traerArchivoInclude()
{
    int nc;
    FILE *arch = fopen (path, "r");
    if (arch == NULL)
        manejoDeErrores(ARCHIVO_INEXISTENTE);
    else
    {
        while ((nc = fgetc(arch))!= EOF)
            putchar(nc);

        fclose(arch);
    }
}

static void manejoDeErrores(error codigo)
{
    switch (codigo)
    {
    case NUMERAL_INCORRECTO:
        printf("\nError: No se forma un #define, #undef o #include \"\n");
        break;

    case TEXTO_DEFINE_INVALIDO:
        printf("\nError: Un #define tiene el texto a reemplazar Invalido\n");
        break;

    case IDENTIFICADOR_INVALIDO:
        printf("\nError: Un #define o un #undef tiene un identificador invalido\n");
        break;

    case PATH_INVALIDO:
        printf("\nError: Path invalido\n");
        break;
    
    default: //ARCHIVO_INEXISTENTE
        printf("\nError: No se encontro el archivo\n");
    }
    exit(0);
}

static void verificarEnTabla()
{ 
    const char *elemento;
    if(elemento = get(palabra))
        printf("%s",elemento);
    else
        printf("%s",palabra);
}

static void textoDefineInvalido(int c) //Texto invalido
{
    manejoDeErrores(TEXTO_DEFINE_INVALIDO);
}

static void identificadorInvalido(int c) //Identificador invalido
{
    manejoDeErrores(IDENTIFICADOR_INVALIDO);
}

static void numeralIncorrecto(int c)
{
    manejoDeErrores(NUMERAL_INCORRECTO);
}

static void pathInvalido(int c)
{
    manejoDeErrores(PATH_INVALIDO);
}

static void nuevoTextoDefine(int c)
{
    contTextoDefine = 0;
    memset(textoDefine,'\0',sizeof(char) * largoMaxTextoDefine);
    textoDefine[contTextoDefine] = c;
}

static void nuevoCaracterTextoDefine(int c)
{
    contTextoDefine++;
    textoDefine[contTextoDefine] = c;
}

static void nuevoPath(int c){
    contPath = 0;
    memset(path,'\0',sizeof(char) * largoMaxPath);
    path[contPath] = c;
}

static void nuevoCaracterPath(int c)
{
    contPath++;
    path[contPath] = c;
}

static void nuevaPalabra(int c)
{
    contPalabra = 0;
    memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
    palabra[contPalabra] = c;    
}

static void nuevoCaracterEnPalabra(int c)
{
    contPalabra++;
    palabra[contPalabra] = c;
}

static void nuevoIdentificador(int c)
{
    contIdentificador = 0;
    memset(identificador,'\0',sizeof(char) * largoMaxIdentificador);
    identificador[contIdentificador] = c;
}

static void nuevoCaracterIdentificador(int c)
{
    contIdentificador++;
    identificador[contIdentificador] = c;
}


