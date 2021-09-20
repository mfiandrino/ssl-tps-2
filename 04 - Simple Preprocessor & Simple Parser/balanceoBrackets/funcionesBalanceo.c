/*
Balanceo de brackets
Modulo con las funciones para el balanceo de brackets para el TP4.
Grupo Nro 3 del curso K2051 Lunes TN
20210920
*/
#include "funcionesBalanceo.h"
#include <stdio.h>
#include <stdlib.h>

/*Funciones varias*/
static char bracketInvertido(char);
static int cierraBracketCorrecto(char, char);
static int atenderClausuraBracket(int);

//--------------ESTADOS--------------------
static void caracterComun(int);
static void aperturaBracket(int);
static void clausuraBracket(int);
static void aperturaComillasSimples(int);
static void caracterComillasSimples(int);
static void clausuraComillasSimples(int);
static void aperturaComillasDobles(int);
static void caracterComillasDobles(int);
static void clausuraComillasDobles(int);
static void caracterContrabarraComillaSimple(int);
static void caracterContrabarraComillaDoble(int);

/*Errores*/
static void errorMasDeUnCaracterEnComillasSimples();
static void errorComillasDentroDeComillasSimples();
static void bracketsNoBalanceados();
void manejoDeErrores(error codigo);

//Asignacion de estado inicial
void (*fun_ptr)(int)= caracterComun;

static void caracterComun(int c)
{
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
}


static void aperturaBracket(int c){
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
}


static void clausuraBracket(int c){
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
}


static void aperturaComillasSimples(int c){
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
}


static void caracterComillasSimples(int c){
    switch (c)
    {
        case '\'':                   
            fun_ptr = &clausuraComillasSimples;
            break;

        default: //EOC                    
            fun_ptr = &errorMasDeUnCaracterEnComillasSimples;
    }
}

static void clausuraComillasSimples(int c){
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
}

static void aperturaComillasDobles(int c){
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
}

static void caracterComillasDobles(int c){
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
}

static void clausuraComillasDobles(int c){
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
}

static void caracterContrabarraComillaSimple(int c){
    fun_ptr = &caracterComillasSimples;
}

static void caracterContrabarraComillaDoble(int c){
    fun_ptr = &caracterComillasDobles;
}

static void bracketsNoBalanceados()
{       
    manejoDeErrores(BRACKETS_NO_BALANCEADOS);
}

static void errorMasDeUnCaracterEnComillasSimples()
{   
    manejoDeErrores(MAS_DE_UN_CARACTER_EN_COMILLAS_SIMPLES);
}
 
static void errorComillasDentroDeComillasSimples()
{  
    manejoDeErrores(COMILLAS_DENTRO_DE_COMILLAS_SIMPLES);
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

void manejoDeErrores(error codigo)
{
    switch (codigo)
    {
    case MAS_DE_UN_CARACTER_EN_COMILLAS_SIMPLES:
        printf("\nError: hay mas de un caracter en unas comillas simples\n");
        break;

    case COMILLAS_DENTRO_DE_COMILLAS_SIMPLES:
        printf("\nError: hay comillas dentro de comillas simples sin usar la contrabarra\n");
        break;
    
    default: //BRACKETS_NO_BALANCEADOS
        printf("\nError: los brackets NO estan balanceados\n");
    }
    exit(0);
}