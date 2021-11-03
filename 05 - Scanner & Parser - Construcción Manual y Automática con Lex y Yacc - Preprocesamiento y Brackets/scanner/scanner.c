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

#define largoMaxConstNumerica 10
int contConstNumerica;
char constNumerica[largoMaxConstNumerica];

/*Funciones varias*/
static void nuevoTextoDefine(int);
static void nuevoCaracterTextoDefine(int);
static void nuevoIdentificador(int);
static void nuevoCaracterIdentificador(int);
static void nuevoLitCadena(int);
static void nuevoCaracterLitCadena(int);
static void nuevoConstNumerica(int);
static void nuevoCaracterConstNumerica(int);
void llenarToken(Token*, TokenType, char*);
int GetNextToken(Token*);
int analisisComentario(Token*);
int analisisIdentificador(Token*,int);
int analisisConstNumerica(Token*,int);
int analisisComillasDobles(Token*);


//--------------ESTADOS--------------------
static int posibleComentario(int, Token*);
static int comentarioFinDeLinea(int, Token*);
static int comentarioMultilinea(int, Token*);
static int posibleFinDeComentarioMultilinea(int, Token*);
static int enIdentificador(int,Token*);
static int aperturaComillasDobles(int, Token*);
static int entreComillasDobles(int, Token*);
static int primerNumHexa(int, Token*);
static int numHexa(int, Token*);
static int numOctal(int, Token*);



/*Puntero a funcion para las maquinas de estado*/
int (*fun_ptr)(int,Token*);

int GetNextToken(Token *token)
{
    int c;
    while ((c = getchar()) == ' ' || c == '\t');
    switch (c)
    {
        case '\n':
            llenarToken(token,NewLine,NULL);
            return 1;
        
        case '/':
            return analisisComentario(token);

        //Punctuators----------------------------
        case '.':
            llenarToken(token,Punctuator,".");
            return 1;

        case '&':
            llenarToken(token,Punctuator,"&");
            return 1;

        case '*':
            llenarToken(token,Punctuator,"*");
            return 1;
            
        case '+':
            llenarToken(token,Punctuator,"+");
            return 1;

        case '-':
            llenarToken(token,Punctuator,"-");
            return 1;

        case ';':
            llenarToken(token,Punctuator,";");
            return 1;

        case ':':
            llenarToken(token,Punctuator,":");
            return 1;

        case '!':
            llenarToken(token,Punctuator,"!");
            return 1;

        case '=':
            if((c=getchar()) == '=')
                llenarToken(token,Punctuator,"==");
            else
            {
                llenarToken(token,Punctuator,"=");
                ungetc(c,stdin);
            }
            return 1;

        case ',':
            llenarToken(token,Punctuator,",");
            return 1;
        //Fin Punctuators----------------------------

        //Brackets----------------------------
        case '(':
            llenarToken(token,LParen,NULL);
            return 1;

        case ')':
            llenarToken(token,RParen,NULL);
            return 1;

        case '[':
            llenarToken(token,LBrack,NULL);
            return 1;

        case ']':
            llenarToken(token,RBrack,NULL);
            return 1;

        case '{':
            llenarToken(token,LBrace,NULL);
            return 1;

        case '}':
            llenarToken(token,RBrace,NULL);
            return 1;
        //Fin Brackets----------------------------

        case '#':
            llenarToken(token,Numeral,NULL);
            return 1;
        
        case '_': case 'A'...'Z': case 'a'...'z':
            return analisisIdentificador(token,c);

        case '0'...'9':
            return analisisConstNumerica(token,c);

        case '\"':
            return analisisComillasDobles(token);

        /*
        case '\'':
            fun_ptr = aperturaComillasSimples;
            break;*/

        case EOF:
            llenarToken(token,FDT,NULL);
            return 0;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 0;
    }
}


//--------------COMENTARIOS----------------------
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
            llenarToken(token,Comentario,NULL);
            return 1;

        default: //EOC
            fun_ptr = comentarioMultilinea;
    }
    return 0;
}

int analisisComentario(Token *t)
{
    int c;
    fun_ptr = posibleComentario;
    while((c=getchar()) != EOF)
    {
        if((fun_ptr)(c,t))
            if(t->type == LexError)
                return false;
            else
                return true;
    }

    //Si sale del while es porque llego un EOF
    llenarToken(t,FDT,NULL);
    return false;
}
//--------------FIN COMENTARIOS----------------------

//--------------IDENTIFICADOR----------------------
static int enIdentificador(int c, Token *token) //Caracteres aptos para un identificador
{
    switch (c)
    {
        case '_': case 'A'...'Z': case 'a'...'z': case '0'...'9':
            nuevoCaracterIdentificador(c);
            fun_ptr = enIdentificador;
            break;

        default: //EOC
            if(strcmp(identificador,"define")==0)
                llenarToken(token,Define,identificador);                
            else if(strcmp(identificador,"undef")==0)
                llenarToken(token,Undefine,identificador);
            else if(strcmp(identificador,"include")==0)
                llenarToken(token,Include,identificador);   
            else if(strcmp(identificador,"ifdef")==0)
                llenarToken(token,Ifdef,identificador);
            else if(strcmp(identificador,"else")==0)
                llenarToken(token,Else,identificador);
            else if(strcmp(identificador,"endif")==0)
                llenarToken(token,Endif,identificador);
            else
                llenarToken(token,Identificador,identificador);

            ungetc(c,stdin);
            return 1;
    }
    return 0;
}

int analisisIdentificador(Token *t, int c)
{
    fun_ptr = enIdentificador;
    nuevoIdentificador(c);
    while((c=getchar()) != EOF)
    {
        if((fun_ptr)(c,t))
            if(t->type == LexError)
                return false;
            else
                return true;
    }

    //Si sale del while es porque llego un EOF
    llenarToken(t,FDT,NULL);
    return false;
}
//--------------FIN IDENTIFICADOR----------------------

//--------------CONSTANTE NUMERICA----------------------

static int baseNumerica(int c, Token *token) //Caracteres aptos para un identificador
{
    switch (c)
    {
        case 'x':
            nuevoCaracterConstNumerica(c);
            fun_ptr = primerNumHexa;
            break;

        case '0'...'7':
            nuevoCaracterConstNumerica(c);
            fun_ptr = numOctal;

        default: //EOC
            ungetc(c,stdin);
            llenarToken(token,ConstNumerica,constNumerica);
            return 1;
    }
    return 0;
}

static int primerNumHexa(int c, Token *token) //Caracteres aptos para un identificador
{
    switch (c)
    {
        case '0'...'9': case 'a'...'f': case 'A'...'F':
            nuevoCaracterConstNumerica(c);
            fun_ptr = numHexa;
            break;

        default: //EOC
            llenarToken(token,LexError,NULL);
            return 1;
    }
    return 0;
}

static int numHexa(int c, Token *token) //Caracteres aptos para un identificador
{
    switch (c)
    {
        case '0'...'9': case 'a'...'f': case 'A'...'F':
            nuevoCaracterConstNumerica(c);
            fun_ptr = numHexa;
            break;

        default: //EOC
            ungetc(c,stdin);
            llenarToken(token,ConstNumerica,constNumerica);
            return 1;
    }
    return 0;
}

static int numOctal(int c, Token *token)
{
    switch (c)
    {
        case '0'...'7':
            nuevoCaracterConstNumerica(c);
            fun_ptr = numOctal;
            break;

        default: //EOC
            ungetc(c,stdin);
            llenarToken(token,ConstNumerica,constNumerica);
            return 1;
    }
    return 0;
}

static int numDecimal(int c, Token *token)
{
    switch (c)
    {
        case '0'...'9':
            nuevoCaracterConstNumerica(c);
            fun_ptr = numDecimal;
            break;

        default: //EOC
            ungetc(c,stdin);
            llenarToken(token,ConstNumerica,constNumerica);
            return 1;
    }
    return 0;
}

int analisisConstNumerica(Token *t, int c)
{
    if(c == '0')
        fun_ptr = baseNumerica;
    else
        fun_ptr = numDecimal;
    nuevoConstNumerica(c);
    while((c=getchar()) != EOF)
    {
        if((fun_ptr)(c,t))
            if(t->type == LexError)
                return false;
            else
                return true;
    }

    //Si sale del while es porque llego un EOF
    llenarToken(t,FDT,NULL);
    return false;
}
//--------------FIN CONSTANTE NUMERICA----------------------


//--------------COMILLAS DOBLES----------------------
static int aperturaComillasDobles(int c, Token *token) //Entramos a las comillas dobles caracteres adentro
{
    switch (c)
    {
        case '\"':
            nuevoLitCadena('\0');
            llenarToken(token,LitCadena,litCadena);
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

int analisisComillasDobles(Token *t)
{
    int c;
    fun_ptr = aperturaComillasDobles;
    while((c=getchar()) != EOF)
    {
        if((fun_ptr)(c,t))
            if(t->type == LexError)
                return false;
            else
                return true;
    }

    //Si sale del while es porque llego un EOF
    llenarToken(t,FDT,NULL);
    return false;
}
//--------------FIN COMILLAS DOBLES----------------------

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

static void nuevoConstNumerica(int c)
{
    contConstNumerica = 0;
    memset(constNumerica,'\0',sizeof(char) * largoMaxConstNumerica);
    constNumerica[contConstNumerica] = c;
}

static void nuevoCaracterConstNumerica(int c)
{
    contConstNumerica++;
    constNumerica[contConstNumerica] = c;
}

void llenarToken(Token *t, TokenType tt, char* valor)
{
    t->type = tt;
    t->val = valor;
}