#include "funcionesPreprocesador.h"
#include "../lookupTable/lookupTable.h"

#define largoMaxIdentificador 32
int contIdentificador;
char identificador[largoMaxIdentificador];

#define largoMaxTextoDefine 100
int contTextoDefine;
char textoDefine[largoMaxTextoDefine];

#define largoMaxPalabra 100
int contPalabra;
char palabra[largoMaxPalabra];


struct nlist *elemento;

static void comentarioFinDeLinea(int);
static void comentarioMultilinea(int);
static void posibleFinDeComentarioMultilinea(int);
static void FinDeComentarioMultilinea(int);
static void posibleComentario(int);
static void enPalabra(int);
static void espacio(int);
static void comienzoDeLinea(int);
static void aperturaComillasSimples(int);
static void entreComillasSimples(int);
static void cierreComillasSimples(int);
static void aperturaComillasDobles(int);
static void cierreComillasDobles(int);
static void entreComillasDobles(int);
static void posibleIncludeDefineUndef(int);
static void d(int);
static void de(int);
static void def(int);
static void defi(int);
static void defin(int);
static void define(int);
static void defineEspacio(int);
static void defineIdentificador(int);
static void identificadorInvalido(int);
static void defineIdentificadorEspacio(int);
static void textoDefineInvalido(int);
static void defineTexto(int);
static void u(int);
static void un(int);
static void und(int);
static void unde(int);
static void esUndef(int);
static void undefEspacio(int);
static void undefIdentificador(int);
static void textoUndefInvalido(int);
static void caracterEspecial(int);



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

        case ' ': case '\t':
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &caracterEspecial;
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
            putchar('/');
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            putchar('/');
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '*':
            fun_ptr = &comentarioMultilinea;
            break;

        case ' ': case '\t':
            putchar('/');
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            putchar('/');
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            putchar('/');
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void enPalabra(int c) //Caracteres aptos para un identificador
{
    switch (c)
    {
        case '\n':
            //Comparar con tabla de define y fijarse de reemplazar o imprimir la palabra
            if(elemento = lookup(palabra))
                printf("%s",elemento->define);
            else
                printf("%s",palabra);

            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '\'':
            //Comparar con tabla de define y fijarse de reemplazar o imprimir la palabra
            if(elemento = lookup(palabra))
                printf("%s",elemento->define);
            else
                printf("%s",palabra);

            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            //Comparar con tabla de define y fijarse de reemplazar o imprimir la palabra
            if(elemento = lookup(palabra))
                printf("%s",elemento->define);
            else
                printf("%s",palabra);
                
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '/':
            //Comparar con tabla de define y fijarse de reemplazar o imprimir la palabra
            if(elemento = lookup(palabra))
                printf("%s",elemento->define);
            else
                printf("%s",palabra);
                
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            //Comparar con tabla de define y fijarse de reemplazar o imprimir la palabra
            if(elemento = lookup(palabra))
                printf("%s",elemento->define);          
            else
                printf("%s",palabra);
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            contPalabra++;
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            if(elemento = lookup(palabra))
                printf("%s",elemento->define);          
            else
                printf("%s",palabra);
            putchar(c);
            fun_ptr = &caracterEspecial;
            break;
    }
}

static void espacio(int c) //Caracter comun
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

        case ' ': case '\t':
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void caracterEspecial(int c) //Caracter especial (distintos a los que puede ser un indentificador)
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

        case ' ': case '\t':
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &caracterEspecial;
            
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

        case '#':
            fun_ptr = &posibleIncludeDefineUndef;
            break;

        case '\'':
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case ' ': case '\t':
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &caracterEspecial;
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

        case ' ': case '\t':
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void aperturaComillasDobles(int c) //Entramos a las comillas dobles caracteres adentro
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

static void cierreComillasDobles(int c) //Cierre de comillas dobles, se busca el siguiente caracter
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

        case ' ': case '\t':
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            putchar(c);
            fun_ptr = &caracterEspecial;
    }

}

static void entreComillasDobles(int c) //Entre comillas dobles, se buscan los caracteres adentro de las
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

static void posibleIncludeDefineUndef(int c) //Tengo un # Busco una 'd' 'i' 'u'
{
    switch (c)
    {
        case 'd':
            fun_ptr = &d;
            break;

        case 'u':
            fun_ptr = &u;
            break;

        case '\'':
            putchar('#');
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            putchar('#');
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            putchar('#');
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            putchar('#');
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            putchar('#');
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'c': case 'e'...'t': case 'v'...'z':
            putchar('#');
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            putchar('#');
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void d(int c) // Encuentro una 'd' buscamos completar el define
{
    switch (c)
    {
        case 'e':
            fun_ptr = &de;
            break;

        case '\'':
            printf("%s","#d");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#d");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#d");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#d");
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            printf("%s","#d");
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'d': case 'f'...'z':
            printf("%s","#d");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#d");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void de(int c) // Encuentro una 'de' buscamos completar el define
{
    switch (c)
    {
        case 'f':
            fun_ptr = &def;
            break;

        case '\'':
            printf("%s","#de");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#de");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#de");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#de");
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            printf("%s","#de");
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'e': case 'g'...'z':
            printf("%s","#de");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC 
            printf("%s","#de");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void def(int c) // Encuentro una 'def' buscamos completar el define
{
    switch (c)
    {
        case 'i':
            fun_ptr = &defi;
            break;

        case '\'':
            printf("%s","#def");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#def");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#def");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#def");
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            printf("%s","#def");
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'h': case 'j'...'z':
            printf("%s","#def");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#def");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void defi(int c) // Encuentro una 'defi' buscamos completar el define
{
    switch (c)
    {
        case 'n':
            fun_ptr = &defin;
            break;

        case '\'':
            printf("%s","#defi");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#defi");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#defi");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#defi");
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            printf("%s","#defi");
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'m': case 'o'...'z':
            printf("%s","#defi");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#defi");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void defin(int c) // Encuentro una 'defin' buscamos completar el define
{
    switch (c)
    {
        case 'e':
            fun_ptr = &define;
            break;

        case '\'':
            printf("%s","#defin");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#defin");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#defin");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#defin");
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            printf("%s","#defin");
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'d': case 'f'...'z':
            printf("%s","#defin");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#defin");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void define(int c) // Encuentro una 'define' buscamos espacio para el identificador
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = &defineEspacio;
            break;

        case '\'':
            printf("%s","#define");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#define");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#define");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#define");
            fun_ptr = &posibleComentario;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            printf("%s","#define");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#define");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void defineEspacio(int c) // Espacio en el define, llenamos la palabra del identificador
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z':
            contIdentificador = 0;
            memset(identificador,'\0',sizeof(char) * largoMaxIdentificador);
            identificador[contIdentificador] = c;
            fun_ptr = &defineIdentificador;
            break;

        case ' ': case '\t':
            fun_ptr = &defineEspacio;
            break;

        default: //EOC
            fun_ptr = &identificadorInvalido;
    }
}

static void defineIdentificador(int c) // Identificador completo del define
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            contIdentificador++;
            identificador[contIdentificador] = c;
            fun_ptr = &defineIdentificador;
            break;

        case ' ': case '\t':
            fun_ptr = &defineIdentificadorEspacio;
            break;

        default: //EOC
            fun_ptr = &identificadorInvalido;
    }
}

static void identificadorInvalido(int c) //Identificador invalido
{
    printf("\nIdentificador Invalido");
    exit(0);
}

static void defineIdentificadorEspacio(int c) //Buscamos el texto a reemplazar del idenficador
{
    switch (c)
    {
        case '\n':
            fun_ptr = &textoDefineInvalido;
            break;

        case ' ': case '\t':
            fun_ptr = &defineIdentificadorEspacio;
            break;

        default: //EOC
            contTextoDefine = 0;
            memset(textoDefine,'\0',sizeof(char) * largoMaxTextoDefine);
            textoDefine[contTextoDefine] = c;
            fun_ptr = &defineTexto;
    }
}

static void textoDefineInvalido(int c) //Texto invalido
{
    printf("\nTexto define Invalido");
    exit(0);
}

static void defineTexto(int c) //Texto correspondiente al identificador
{
    switch (c)
    {
        case '\n':
            install(identificador,textoDefine);
            fun_ptr = &comienzoDeLinea;
            break;

        default: //EOC
            contTextoDefine++;
            textoDefine[contTextoDefine] = c;
            fun_ptr = &defineTexto;
    }
}

static void u(int c) // Encuentro una 'u' buscamos completar el undef
{
    switch (c)
    {
        case 'n':
            fun_ptr = &un;
            break;

        case '\'':
            printf("%s","#u");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#u");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#u");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#u");
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            printf("%s","#u");
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'m': case 'o'...'z':
            printf("%s","#u");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#u");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void un(int c)  // Encuentro una 'un' buscamos completar el undef
{
    switch (c)
    {
        case 'd':
            fun_ptr = &und;
            break;

        case '\'':
            printf("%s","#un");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#un");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#un");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#un");
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            printf("%s","#un");
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'c': case 'e'...'z':
            printf("%s","#un");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#un");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }

}

static void und(int c)  // Encuentro una 'und' buscamos completar el undef
{
    switch (c)
    {
        case 'e':
            fun_ptr = &unde;
            break;

        case '\'':
            printf("%s","#und");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#und");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#und");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#und");
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            printf("%s","#und");
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'d': case 'f'...'z':
            printf("%s","#und");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#und");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }

}

static void unde(int c)  // Encuentro una 'unde' buscamos completar el undef
{
    switch (c)
    {
        case 'f':
            fun_ptr = &esUndef;
            break;

        case '\'':
            printf("%s","#unde");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#unde");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#unde");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#unde");
            fun_ptr = &posibleComentario;
            break;

        case ' ': case '\t':
            printf("%s","#unde");
            putchar(c);
            fun_ptr = &espacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'e': case 'g'...'z':
            printf("%s","#unde");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#unde");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void esUndef(int c)  // Encuentro un 'undef'
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = &undefEspacio;
            break;

        case '\'':
            printf("%s","#undef");
            putchar(c);
            fun_ptr = &aperturaComillasSimples;
            break;

        case '\"':
            printf("%s","#undef");
            putchar(c);
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\n':
            printf("%s","#undef");
            putchar(c);
            fun_ptr = &comienzoDeLinea;
            break;

        case '/':
            printf("%s","#undef");
            fun_ptr = &posibleComentario;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            printf("%s","#undef");
            contPalabra = 0;
            memset(palabra,'\0',sizeof(char) * largoMaxPalabra);
            palabra[contPalabra] = c;
            fun_ptr = &enPalabra;
            break;

        default: //EOC
            printf("%s","#undef");
            putchar(c);
            fun_ptr = &caracterEspecial;
    }
}

static void undefEspacio(int c) //Espacio despues del undef, busco el identificador asociado
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z':
            contIdentificador = 0;
            memset(identificador,'\0',sizeof(char) * largoMaxIdentificador);
            identificador[contIdentificador] = c;
            fun_ptr = &undefIdentificador;
            break;

        case ' ': case '\t':
            fun_ptr = &undefEspacio;
            break;

        default: //EOC
            fun_ptr = &identificadorInvalido;
    }

}

static void undefIdentificador(int c) //Identificador asociado al undef, se deja de asociar para el cambio
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            contIdentificador++;
            identificador[contIdentificador] = c;
            fun_ptr = &undefIdentificador;
            break;

        case '\n' :case ' ':
            undef(identificador);
            fun_ptr = &comienzoDeLinea;
            break;

        default: //EOC
            contTextoDefine++;
            textoDefine[contTextoDefine] = c;
            fun_ptr = &undefIdentificador;


    }   
}

static void textoUndefInvalido(int c)
{
    printf("\nTexto undef Invalido");
    exit(0);
}




