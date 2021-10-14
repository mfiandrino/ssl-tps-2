#include "scanner.h"
#include "stdio.h"
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

#define largoMaxLitCadena 100
int contLitCadena;
char litCadena[largoMaxLitCadena];

//--------------ESTADOS--------------------
/*Comentarios*/
static int posibleComentario(int);
static int comentarioFinDeLinea(int);
static int comentarioMultilinea(int);
static int posibleFinDeComentarioMultilinea(int);

/*Generales*/
static int enPalabra(int);
static int comienzoDeLinea(int, Token*);
static int restoDeLinea(int);

/*Comillas*/
static int aperturaComillasSimples(int);
static int entreComillasSimples(int);
static int aperturaComillasDobles(int);
static int entreComillasDobles(int);

/*Define, Undef e Include*/
static int posibleIncludeDefineUndef(int);

static int d(int);
static int de(int);
static int def(int);
static int defi(int);
static int defin(int);
static int define(int);
static int defineEspacio(int);
static int defineIdentificador(int);
static int defineIdentificadorEspacio(int);
static int defineTexto(int);

static int u(int);
static int un(int);
static int und(int);
static int unde(int);
static int esUndef(int);
static int undefEspacio(int);
static int undefIdentificador(int);

static int i(int);
static int in(int);
static int inc(int);
static int incl(int);
static int inclu(int);
static int includ(int);
static int include(int);
static int includeComillas(int);
static int includePath(int);

/*Errores*/
static int textoDefineInvalido(int);
static int identificadorInvalido(int);
static int numeralIncorrecto(int);
static int pathInvalido(int);
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
static void nuevoLitCadena(int);
static void nuevoCaracterLitCadena(int);

int (*fun_ptr)(int,Token*)= comienzoDeLinea;

bool GetNextToken(Token *t)
{
    int c;
    int resultado;
    while ((c=getchar())!= EOF) 
    {
        resultado = (fun_ptr)(c,t);
        if(resultado)
            return true;
    }
    return false;
}


/*
#include <stdio.h>
//mati capo\n

token Comentario
token identi "mati"

*/
void llenarToken(Token *t, TokenType tt, char* valor)
{
    t->type = tt;
    t->val = valor;
}

static int comienzoDeLinea(int c , Token *token) //Despues de un \n o al principio del archivo
{
    switch (c)
    {
        case '\n':
            fun_ptr = comienzoDeLinea;
            break;

        case '/':
            fun_ptr = posibleComentario;
            break;

        case '#':
            fun_ptr = posibleIncludeDefineUndef;
            llenarToken(token,Numeral,NULL);
            return 1;

        case '\'':
            nuevoLitCadena(c);
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            nuevoLitCadena(c);
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
    return 0;
}

static int comentarioFinDeLinea(int c, Token *token) //Dentro de un comentario de linea
{
    switch (c)
    {
        case '\n':
            fun_ptr = comienzoDeLinea;
            llenarToken(token,Comentario,NULL);
            return 1;

        default: //EOC
            fun_ptr = comentarioFinDeLinea;
    }
    return 0;
}

static int comentarioMultilinea(int c, Token *token) //Dentro de comentario multilinea
{
    switch (c)
    {
        case '*':
            fun_ptr = posibleFinDeComentarioMultilinea;
            break;

        default: //EOC
            fun_ptr = comentarioMultilinea;
    }
    return 0;
}

static int posibleFinDeComentarioMultilinea(int c, Token *token) //Dentro de comentario multilinea, posible fin del mismo
{
    switch (c)
    {
        case '*':
            fun_ptr = posibleFinDeComentarioMultilinea;
            break;

        case '/':
            fun_ptr = restoDeLinea;
            llenarToken(token,Comentario,NULL);
            return 1;

        default: //EOC
            fun_ptr = comentarioMultilinea;
    }
    return 0;
}


/*
char *nombre = "Maxi";

token IDENTIFICADOR "char"
token PUNCTUATION "*"
token IDENTIFICADOR "nombre"
token PUNCTUATION "="
token LITERAL-CADENA "Maxi"
token PUNCTUATION ";"


char a = 'h';

ID char
ID a
PUNC =
no se
PUNC ;
*/

static int restoDeLinea(int c) //Fin de comentario multilinea, siguiente caracter
{
    switch (c)
    {
        case '/':
            fun_ptr = posibleComentario;
            break;

        case '\'':
            fun_ptr = aperturaComillasSimples;
            break;

        case '\"':
            fun_ptr = aperturaComillasDobles;
            break;

        case '\n':
            fun_ptr = comienzoDeLinea;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevaPalabra(c);
            fun_ptr = enPalabra;
            break;

        default: //EOC
            fun_ptr = restoDeLinea;
    }
}

static int posibleComentario(int c, Token* token) //Llego una / vemos siguiente caracter
{
    switch (c)
    {
        case '/':
            fun_ptr = comentarioFinDeLinea;
            break;

        case '*':
            fun_ptr = comentarioMultilinea;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
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

static int aperturaComillasSimples(int c, Token *token) //Apertura comillas simples
{
    switch (c)
    {
        case '\'':
            llenarToken(token,LitCadena,litCadena);
            fun_ptr = restoDeLinea;
            return 1;

        case '\n':
            llenarToken(token,LexError,NULL);
            return 1;

        default: //EOC
            nuevoCaracterLitCadena(c);
            fun_ptr = entreComillasSimples;
    }
    return 0;
}

static int entreComillasSimples(int c, Token *token) //Dentro de comillas simples
{
    switch (c)
    {
        case '\'':
            llenarToken(token,LitCadena,litCadena);
            fun_ptr = restoDeLinea;
            return 1;

        case '\n':
            llenarToken(token,LexError,NULL);
            return 1;

        default: //EOC
            nuevoCaracterLitCadena(c);
            fun_ptr = entreComillasSimples;
    }
    return 0;
}


static int aperturaComillasDobles(int c, Token *token) //Entramos a las comillas dobles caracteres adentro
{
    switch (c)
    {
        case '\"':
            fun_ptr = restoDeLinea;
            llenarToken(token,LitCadena,litCadena);
            return 1;

        case '\n':
            llenarToken(token,LexError,NULL);
            return 1;

        default: //EOC
            nuevoCaracterLitCadena(c);         
            fun_ptr = entreComillasDobles;
    }
}

static int entreComillasDobles(int c, Token *token) //Entre comillas dobles, se buscan los caracteres adentro de las
{
    switch (c)
    {
        case '\"':
            fun_ptr = restoDeLinea;
            llenarToken(token,LitCadena,litCadena);
            return 1;

        case '\n':
            llenarToken(token,LexError,NULL);
            return 1;

        default: //EOC
            nuevoCaracterLitCadena(c);         
            fun_ptr = entreComillasDobles;
    }
}

static int posibleIncludeDefineUndef(int c, Token *token) //Tengo un # Busco una 'd' 'u' 'i'
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
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int d(int c, Token *token) // Encuentro una 'd' buscamos completar el define
{
    switch (c)
    {
        case 'e':
            fun_ptr = de;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int de(int c, Token *token) // Encuentro una 'de' buscamos completar el define
{
    switch (c)
    {
        case 'f':
            fun_ptr = def;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int def(int c, Token *token) // Encuentro una 'def' buscamos completar el define
{
    switch (c)
    {
        case 'i':
            fun_ptr = defi;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int defi(int c, Token *token) // Encuentro una 'defi' buscamos completar el define
{
    switch (c)
    {
        case 'n':
            fun_ptr = defin;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int defin(int c, Token *token) // Encuentro una 'defin' buscamos completar el define
{
    switch (c)
    {
        case 'e':
            fun_ptr = define;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int define(int c, Token *token) // Encuentro una 'define' buscamos espacio para el identificador
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = defineEspacio;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int defineEspacio(int c, Token *token) // Espacio en el define, llenamos la palabra del identificador
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z':
            llenarToken(token,Define,NULL);
            nuevoIdentificador(c);
            fun_ptr = defineIdentificador;
            return 1;

        case ' ': case '\t':
            fun_ptr = defineEspacio;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int defineIdentificador(int c, Token *token) // Identificador completo del define
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            nuevoCaracterIdentificador(c);
            fun_ptr = defineIdentificador;
            break;

        case ' ': case '\t':
            llenarToken(token,Identificador,identificador);
            fun_ptr = defineIdentificadorEspacio;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int defineIdentificadorEspacio(int c, Token *token) //Buscamos el texto a reemplazar del idenficador
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = defineIdentificadorEspacio;
            break;

        default: //EOC
            nuevoTextoDefine(c);
            fun_ptr = defineTexto;
    }
    return 0;
}

static int defineTexto(int c, Token *token) //Texto correspondiente al identificador
{
    switch (c)
    {
        case '\n':
            llenarToken(token,TextoReemplazo,textoDefine);
            set(identificador,textoDefine);
            fun_ptr = comienzoDeLinea;
            return 1;

        default: //EOC
            nuevoCaracterTextoDefine(c);
            fun_ptr = defineTexto;
    }
    return 0;
}
//Llegamos hasta aca
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
}

static int i(int c) // Encuentro una 'i' buscamos completar el include
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

static int in(int c) // Encuentro una 'in' buscamos completar el include
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

static int inc(int c) //Encuentro una 'inc' buscamos completar el include
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

static int incl(int c) // Encuentro una 'incl' buscamos completar el include
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

static int inclu(int c) // Encuentro una 'inclu' buscamos completar el include
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

static int includ(int c) // Encuentro una 'includ' buscamos completar el include
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

static int include(int c) // Encuentro un 'include' buscamos espacio para el path
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

static int includeComillas(int c) // Comillas en el include, llenamos la palabra del path
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

static int includePath(int c) // Path completo del include
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

static void nuevoLitCadena(int c)
{
    contLitCadena = 0;
    memset(litCadena,'\0',sizeof(char) * largoMaxLitCadena);
    litCadena[contLitCadena] = c;
}

static void nuevoCaracterLitCadena(int c)
{
    contLitCadena++;
    litCadena[contLitCadena] = c;
}
/*
typedef enum {
 Comentario,
 Numeral,
 Define,
 Undefine,
 Ifdef,
 Endif,
 Include,
 Path,              VALOR
 Identificador,     VALOR
 TextoReemplazo,    VALOR
 LParen='(',
 RParen=')',
 LBrack='[',
 RBrack=']',
 LBrace='{',
 RBrace='}',
 Punctuator,        VALOR
 LexError
} TokenType;
*/
/*
= Scanner

Tipos de Token
1. Comentario
2. Numeral
3. DEFINE
4. UNDEFINE
5. INCLUDE
6. IDENTIFICADOR
7. TEXTOREEMPLAZO
8. PUNTCTUATOR

TEst

Input

#define MAX 10
int a=MAX;
return a;

Output del Scanner
NUMEREAL
DEFINE
IDENTIFICADOR,    "MAX"
TEXTOREEMPLAZO,    "10"
IDENTIFCADOR,    "int"
IDENTIFICADOR,    "a"
PUNCTUATOR,        "="
IDENTIFICADOR,    "MAX"
PUNCTUATOR,        ";"
IDENTIFICADOR,     "return"
IDENTIFICADOR,    "a"
PUNCTUATOR,        ";"

Output del Preprocesadpr

Alternativa 1
    int a=10; return a;

Alternativa 2
    int a=10;
    return a;

Token GetNextToken(void);

struct Token{
    TipoDeToken tipo;
    char* valor;
};
typedef struct Token Token;

enum TipoDeToken{
    ...
}

typedef enum TipoDeToken TipoDeToken;

= Parser
Invoca a GetNextToken mientras el token retornado no sea FDT o Error.

GIC

OB -> S P
S -> Art Sust
P -> Verbo

Ejemplo
#define MAX 10
int a=MAX; // Es un 10
return a; // hola
chau //

UnidadDeTraducción ->
    Componente
    UnidadDeTraducción Componente
    
X ->
    Token
    { X }
    [ X ]
    ( X )
    
Ejemplo de Parseo
({hola})

X
( X )
( { X } )
( { Token } )
( { Identificador } )
( { hola } )
    
Componente ->
    Directiva
    Comentario
    Identificador
    Punctator

Directiva ->
    NUMERAL DEFINE IDENTIFICADOR TEXTODEREEMPLAZO NL?
    NUMERAL UNDEFINE IDENTIFICADOR NL?
    NUMERAL INCLUDE PATH //"" <>
    
ASDR
*/