/*
Balanceo de brackets
Modulo con las funciones para el balanceo de brackets para el TP4.
Grupo Nro 3 del curso K2051 Lunes TN
20210905
*/
#include "funcionesBalanceo.h"

static char bracketInvertido(char);
static int cierraBracketCorrecto(char, char);
static int atenderClausuraBracket(int);

//static int caracterComun(int);
static int aperturaBracket(int);
static int clausuraBracket(int);
static int aperturaComillasSimples(int);
static int caracterComillasSimples(int);
static int clausuraComillasSimples(int);
static int aperturaComillasDobles(int);
static int caracterComillasDobles(int);
static int clausuraComillasDobles(int);
//
static int errorMasDeUnCaracterEnComillasSimples();
static int errorComillasDentroDeComillasSimples();
static int caracterContrabarraComillaSimple(int);
static int caracterContrabarraComillaDoble(int);
//
static int bracketsNoBalanceados();


int caracterComun(int c){
    switch (c)
    {
        case '{': case '[': case '(':
            push(c);
            fun_ptr = &aperturaBracket;                            
            break;

        case '}': case ']': case ')':
            if(atenderClausuraBracket(c))
                fun_ptr = &clausuraBracket;
            else 
                fun_ptr = &bracketsNoBalanceados;                                
            break;

        case '\'': 
            fun_ptr = &aperturaComillasSimples;
            break;      

        case '\"':
            fun_ptr = &aperturaComillasDobles;                            
            break;

        default: //EOC
            fun_ptr = &caracterComun;                                                 
    }
    return 1;                    
}


static int aperturaBracket(int c){
    switch (c)
    {
        case '{': case '[': case '(':
            push(c);
            fun_ptr =  &aperturaBracket;                        
            break;

        case '}': case ']': case ')':
            if(atenderClausuraBracket(c))
                fun_ptr = &clausuraBracket;                           
            else 
                fun_ptr = &bracketsNoBalanceados;                            
            break;
            
        case '\'': 
            fun_ptr = &aperturaComillasSimples;                       
            break;
        
        case '\"':
            fun_ptr = &aperturaComillasDobles;                       
            break;

        default: //EOC
            fun_ptr = &caracterComun;                        
    }    
    return 1;            
}


static int clausuraBracket(int c){
    switch (c)
    {
        case '{': case '[': case '(':
            push(c);
            fun_ptr = &aperturaBracket;
            break;

        case '}': case ']': case ')':
            if(atenderClausuraBracket(c))
                fun_ptr = &clausuraBracket;                           
            else                             
                fun_ptr = &bracketsNoBalanceados;
            break;

        case '\'':                         
            fun_ptr = &aperturaComillasSimples;
            break;
        
        case '\"':                        
            fun_ptr = &aperturaComillasDobles;
            break;

        default: //EOC                        
            fun_ptr = &caracterComun;
    }  
    return 1;              
}


static int aperturaComillasSimples(int c){
    switch (c)
    {
        case '\\':                        
            fun_ptr = &caracterContrabarraComillaSimple;
            break;

        case '\'': case '\"':                        
            fun_ptr = &errorComillasDentroDeComillasSimples;
            break;

        default:                        
            fun_ptr = &caracterComillasSimples;
    }    
    return 1;           
}


static int caracterComillasSimples(int c){
    switch (c)
    {
        case '\'':                   
            fun_ptr = &clausuraComillasSimples;
            break;

        default: //EOC                    
            fun_ptr = &errorMasDeUnCaracterEnComillasSimples;
    }
    return 1;
}

static int clausuraComillasSimples(int c){
    switch (c)
    {
        case '\"':                    
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\'':                    
            fun_ptr = &aperturaComillasSimples;
            break;

        case '{': case '[': case '(':                   
            push(c);
            fun_ptr = &aperturaBracket;
            break;

        case '}': case ']': case ')':
            if(atenderClausuraBracket(c))                       
                fun_ptr = &clausuraBracket;
            else                        
                fun_ptr = &bracketsNoBalanceados;
            break;

        default: //EOC                    
            fun_ptr = &caracterComun;
    }
    return 1;
}

static int aperturaComillasDobles(int c){
    switch (c)
    {
        case '\\':                    
            fun_ptr = &caracterContrabarraComillaDoble;
            break;

        case '\"':                                   
            fun_ptr = &clausuraComillasDobles;
            break;

        default: //EOC                   
            fun_ptr = &caracterComillasDobles;
    }
    return 1;
}

static int caracterComillasDobles(int c){
    switch (c)
    {
        case '\\':                    
            fun_ptr = &caracterContrabarraComillaDoble;
            break;

        case '\"':                   
            fun_ptr = &clausuraComillasDobles;
            break;

        default: //EOC                    
            fun_ptr = &caracterComillasDobles;
    }
    return 1;
}

static int clausuraComillasDobles(int c){
    switch (c)
    {
        case '\"':                    
            fun_ptr = &aperturaComillasDobles;
            break;

        case '\'':                    
            fun_ptr = &aperturaComillasSimples;
            break;

        case '{': case '[': case '(':                   
            push(c);
            fun_ptr = &aperturaBracket;
            break;

        case '}': case ']': case ')':
            if(atenderClausuraBracket(c))                        
                fun_ptr = &clausuraBracket;
            else                         
                fun_ptr = &bracketsNoBalanceados;
            break;

        default: //EOC                   
            fun_ptr = &caracterComun;
    }
    return 1;
}

static int caracterContrabarraComillaSimple(int c){
    fun_ptr = &caracterComillasSimples;
    return 1;
}

static int caracterContrabarraComillaDoble(int c){
    fun_ptr = &caracterComillasDobles;
    return 1;
}

static int bracketsNoBalanceados(){       
    return -1;
}

static int errorMasDeUnCaracterEnComillasSimples(){   
    return -2;
}
 
static int errorComillasDentroDeComillasSimples(){  
    return -3;
}

 


static char bracketInvertido(char bracket)
{
    switch(bracket)
    {
        case '{': 
            return '}';
        case '[':
            return ']';
        default:
            return ')';
    }
}

static int cierraBracketCorrecto(char c, char bracket)
{
    bracket = bracketInvertido(bracket);
    if(bracket == c)
        return 1;
    return 0;
}

static int atenderClausuraBracket(int caracter)
{
    char bracket;
    if(pop(&bracket) && cierraBracketCorrecto(caracter,bracket))
        return 1;
    else 
        return 0;
}