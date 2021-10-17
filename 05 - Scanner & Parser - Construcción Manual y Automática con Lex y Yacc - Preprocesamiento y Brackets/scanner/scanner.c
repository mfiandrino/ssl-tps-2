#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define largoMaxIdentificador 32
int contIdentificador;
char identificador[largoMaxIdentificador];

#define largoMaxTextoDefine 100
int contTextoDefine;
char textoDefine[largoMaxTextoDefine];

#define largoMaxLitCadena 100
int contLitCadena;
char litCadena[largoMaxLitCadena];

//--------------ESTADOS--------------------
/*Comentarios*/
static int posibleComentario(int, Token*);
static int comentarioFinDeLinea(int, Token*);
static int comentarioMultilinea(int, Token*);
static int posibleFinDeComentarioMultilinea(int, Token*);

/*Generales*/
static int enIdentificador(int,Token*);
static int nuevoLexema(int,Token*);

/*Comillas
static int aperturaComillasSimples(int);
static int entreComillasSimples(int);*/
static int aperturaComillasDobles(int, Token*);
static int entreComillasDobles(int, Token*);

/*Define, Undef e Include*/
static int posibleIncludeDefineUndef(int, Token*);

static int d(int, Token*);
static int de(int, Token*);
static int def(int, Token*);
static int defi(int, Token*);
static int defin(int, Token*);
static int define(int, Token*);
static int defineEspacio(int, Token*);
static int defineIdentificador(int, Token*);
static int defineIdentificadorEspacio(int, Token*);
static int defineTexto(int, Token*);

static int u(int, Token*);
static int un(int, Token*);
static int und(int, Token*);
static int unde(int, Token*);

static int i(int, Token*);
static int in(int, Token*);
static int inc(int, Token*);
static int incl(int, Token*);
static int inclu(int, Token*);
static int includ(int, Token*);
//--------------FIN ESTADOS-----------------


/*Funciones varias*/
static void nuevoTextoDefine(int);
static void nuevoCaracterTextoDefine(int);
static void nuevoIdentificador(int);
static void nuevoCaracterIdentificador(int);
static void nuevoLitCadena(int);
static void nuevoCaracterLitCadena(int);
void llenarToken(Token*, TokenType, char*);

/*Estado Inicial*/
int (*fun_ptr)(int,Token*)= nuevoLexema;


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
    llenarToken(t,FDT,NULL);
    return false;
}

static int nuevoLexema(int c , Token *token) //Despues de un \n o al principio del archivo3
{
    switch (c)
    {
        case '\n':
            llenarToken(token,NewLine,NULL);
            fun_ptr = nuevoLexema;
            return 1;
        
        case '/':
            fun_ptr = posibleComentario;
            break;

        //Punctuators----------------------------
        case '.':
            fun_ptr = nuevoLexema;
            llenarToken(token,Punctuator,".");
            return 1;

        case '&':
            fun_ptr = nuevoLexema;
            llenarToken(token,Punctuator,"&");
            return 1;

        case '*':
            fun_ptr = nuevoLexema;
            llenarToken(token,Punctuator,"*");
            return 1;
            
        case '+':
            fun_ptr = nuevoLexema;
            llenarToken(token,Punctuator,"+");
            return 1;

        case '-':
            fun_ptr = nuevoLexema;
            llenarToken(token,Punctuator,"-");
            return 1;

        case ';':
            fun_ptr = nuevoLexema;
            llenarToken(token,Punctuator,";");
            return 1;

        case ':':
            fun_ptr = nuevoLexema;
            llenarToken(token,Punctuator,":");
            return 1;

        case '!':
            fun_ptr = nuevoLexema;
            llenarToken(token,Punctuator,"!");
            return 1;

        case '=':
            fun_ptr = nuevoLexema;
            llenarToken(token,Punctuator,"=");
            return 1;

        case ',':
            fun_ptr = nuevoLexema;
            char stringDeC [2];
            llenarToken(token,Punctuator,",");
            return 1;
        //Fin Punctuators----------------------------

        //Brackets----------------------------
        case '(':
            fun_ptr = nuevoLexema;
            llenarToken(token,LParen,NULL);
            return 1;

        case ')':
            fun_ptr = nuevoLexema;
            llenarToken(token,RParen,NULL);
            return 1;

        case '[':
            fun_ptr = nuevoLexema;
            llenarToken(token,LBrack,NULL);
            return 1;

        case ']':
            fun_ptr = nuevoLexema;
            llenarToken(token,RBrack,NULL);
            return 1;

        case '{':
            fun_ptr = nuevoLexema;
            llenarToken(token,LBrace,NULL);
            return 1;

        case '}':
            fun_ptr = nuevoLexema;
            llenarToken(token,RBrace,NULL);
            return 1;
        //Fin Brackets----------------------------

        case '#':
            fun_ptr = posibleIncludeDefineUndef;
            llenarToken(token,Numeral,NULL);
            return 1;

        case ' ':
            fun_ptr = nuevoLexema;
            break;
        
        /*
        case '\'':
            fun_ptr = aperturaComillasSimples;
            break;*/

        case '\"':
            fun_ptr = aperturaComillasDobles;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevoIdentificador(c);
            fun_ptr = enIdentificador;
            break;
        
        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    
    return 0;
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
            llenarToken(token,Define,NULL);
            fun_ptr = define;
            return 1;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int define(int c, Token *token) // Encuentro una 'defin' buscamos completar el define
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

static int defineEspacio(int c, Token *token) // Encuentro una 'defin' buscamos completar el define
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = defineEspacio;
            break;

        case '_': case 'A'...'Z': case 'a'...'z':
            nuevoIdentificador(c);
            fun_ptr = defineIdentificador;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int defineIdentificador(int c, Token *token) //Caracteres aptos para un identificador
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            nuevoCaracterIdentificador(c);
            fun_ptr = defineIdentificador;
            break;

        case ' ': case '\t':
            llenarToken(token,Identificador,identificador);
            ungetc(c,stdin);
            fun_ptr = defineIdentificadorEspacio;
            return 1;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int defineIdentificadorEspacio(int c, Token *token)
{
    switch (c)
    {
        case ' ': case '\t':
            fun_ptr = defineIdentificadorEspacio;
            break;

        case '\n':
            llenarToken(token,LexError,NULL);
            return 1;

        default: //EOC
            nuevoTextoDefine(c);
            fun_ptr = defineTexto;
            break;
    }
    return 0;
}

static int defineTexto(int c, Token *token)
{
    switch (c)
    {
        case '\n':
            llenarToken(token,TextoReemplazo,textoDefine);
            ungetc(c,stdin);
            fun_ptr = nuevoLexema;
            return 1;

        default: //EOC
            nuevoCaracterTextoDefine(c);
            fun_ptr = defineTexto;
            break;
    }
    return 0;
}

static int u(int c, Token *token) // Encuentro una 'u' buscamos completar el undef
{
    switch (c)
    {
        case 'n':
            fun_ptr = un;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int un(int c, Token *token)  // Encuentro una 'un' buscamos completar el undef
{
    switch (c)
    {
        case 'd':
            fun_ptr = und;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;;
    }
    return 0;
}

static int und(int c, Token *token)  // Encuentro una 'und' buscamos completar el undef
{
    switch (c)
    {
        case 'e':
            fun_ptr = unde;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int unde(int c, Token *token)  // Encuentro una 'unde' buscamos completar el undef
{
    switch (c)
    {
        case 'f':
            llenarToken(token,Undefine,NULL);
            fun_ptr = nuevoLexema;
            return 1;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int i(int c, Token *token) // Encuentro una 'i' buscamos completar el include
{
    switch (c)
    {
        case 'n':
            fun_ptr = in;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int in(int c, Token *token) // Encuentro una 'in' buscamos completar el include
{
    switch (c)
    {
        case 'c':
            fun_ptr = inc;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int inc(int c, Token *token) //Encuentro una 'inc' buscamos completar el include
{
    switch (c)
    {
        case 'l':
            fun_ptr = incl;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int incl(int c, Token *token) // Encuentro una 'incl' buscamos completar el include
{
    switch (c)
    {
        case 'u':
            fun_ptr = inclu;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int inclu(int c, Token *token) // Encuentro una 'inclu' buscamos completar el include
{
    switch (c)
    {
        case 'd':
            fun_ptr = includ;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int includ(int c, Token *token) // Encuentro una 'includ' buscamos completar el include
{
    switch (c)
    {
        case 'e':
            llenarToken(token,Include,NULL);
            fun_ptr = nuevoLexema;
            return 1;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int enIdentificador(int c, Token *token) //Caracteres aptos para un identificador
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            nuevoCaracterIdentificador(c);
            fun_ptr = enIdentificador;
            break;

        default: //EOC
            llenarToken(token,Identificador,identificador);
            ungetc(c,stdin);
            fun_ptr = nuevoLexema;
            return 1;
    }
    return 0;
}

static int aperturaComillasDobles(int c, Token *token) //Entramos a las comillas dobles caracteres adentro
{
    switch (c)
    {
        case '\"':
            llenarToken(token,LitCadena,litCadena);
            fun_ptr = nuevoLexema;
            return 1;

        case '\n':
            llenarToken(token,LexError,NULL);
            return 1;

        default: //EOC
            nuevoLitCadena(c);         
            fun_ptr = entreComillasDobles;
    }
    return 0;
}

static int entreComillasDobles(int c, Token *token) //Entre comillas dobles, se buscan los caracteres adentro de las
{
    switch (c)
    {
        case '\"':
            llenarToken(token,LitCadena,litCadena);
            fun_ptr = nuevoLexema;
            return 1;

        case '\n':
            llenarToken(token,LexError,NULL);
            return 1;

        default: //EOC
            nuevoCaracterLitCadena(c);         
            fun_ptr = entreComillasDobles;
    }
    return 0;
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

static int comentarioFinDeLinea(int c, Token *token) //Dentro de un comentario de linea
{
    switch (c)
    {
        case '\n':
            fun_ptr = nuevoLexema;
            ungetc(c,stdin);
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
            fun_ptr = nuevoLexema;
            llenarToken(token,Comentario,NULL);
            return 1;

        default: //EOC
            fun_ptr = comentarioMultilinea;
    }
    return 0;
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

void llenarToken(Token *t, TokenType tt, char* valor)
{
    t->type = tt;
    t->val = valor;
}