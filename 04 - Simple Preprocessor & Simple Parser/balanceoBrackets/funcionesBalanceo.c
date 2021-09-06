/*
Balanceo de brackets
Modulo con las funciones para el balanceo de brackets para el TP4.
Grupo Nro 3 del curso K2051 Lunes TN
20210902
*/
#include "funcionesBalanceo.h"

typedef enum {
    CARACTER_COMUN,
    APERTURA_BRACKET,
    CLAUSURA_BRACKET,
    APERTURA_COMILLAS_SIMPLES,
    CARACTER_COMILLAS_SIMPLES,
    CLAUSURA_COMILLAS_SIMPLES,
    APERTURA_COMILLAS_DOBLES,
    CARACTER_COMILLAS_DOBLES,
    CLAUSURA_COMILLAS_DOBLES,
    ERROR_MAS_DE_UN_CARACTER_EN_COMILLAS_SIMPLES,
    ERROR_COMILLAS_DENTRO_DE_COMILLAS_SIMPLES,
    CARACTER_CONTRABARRA_COMILLA_SIMPLE,
    CARACTER_CONTRABARRA_COMILLA_DOBLE,
    BRACKETS_NO_BALANCEADOS
}state;

static char bracketInvertido(char);
static int cierraBracketCorrecto(char, char);
static int atenderClausuraBracket(int);

static void caracterComun(int);
static void aperturaBracket(int);
static void clausuraBracket(int);
static void aperturaComillasSimples(int);
static void caracterComillasSimples(int);
static void clausuraComillasSimples(int);
static void aperturaComillasDobles(int);
static void caracterComillasDobles(int);
static void clausuraComillasDobles(int);
static int errorMasDeUnCaracterEnComillasSimples();
static int errorComillasDentroDeComillasSimples();
static void caracterContrabarraComillaSimple(int);
static void caracterContrabarraComillaDoble(int);
static int bracketsNoBalanceados();


static void caracterComun(int c){
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


static void clausuraBrackets(int c){
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
                    push(pila,c);
                    fun_ptr = &aperturaBracket;
                    break;

                case '}': case ']': case ')':
                    if(atenderClausuraBracket(pila,c))                       
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
                    push(pila,c);
                    fun_ptr = &aperturaBracket;
                    break;

                case '}': case ']': case ')':
                    if(atenderClausuraBracket(pila,c))                        
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

static int bracketsNoBalanceados(){
    return -1;
}

static int errorMasDeUnCaracterEnComillasSimples(){
    return -2;
}
 
static int errorComillasDentroDeComillasSimples(){
    return -3;
}

 


int balanceoDeBrackets()
{
    int c;
    inicializarPila();
    fun_ptr = &caracterComun;
    while ((c = getchar() != EOF)){
         (*fun_ptr)(c);
    }
}



int balanceoDeBrackets()
{
    int c;
    inicializarPila();   
    state s = CARACTER_COMUN;

    while ((c=getchar())!= EOF) 
    {
        switch (s)
        {
            case CARACTER_COMUN:
                switch (c)
                {
                    case '{': case '[': case '(':
                        s = APERTURA_BRACKET;
                        push(pila,c);
                        break;

                    case '}': case ']': case ')':
                        if(atenderClausuraBracket(pila,c))
                            s = CLAUSURA_BRACKET;
                        else 
                            s = BRACKETS_NO_BALANCEADOS;
                        break;

                    case '\'':                     
                        s = APERTURA_COMILLAS_SIMPLES;
                        break;      

                    case '\"':
                        s = APERTURA_COMILLAS_DOBLES;
                        break;

                    default: //EOC
                        s = CARACTER_COMUN;                        
                }
                break;

            case APERTURA_BRACKET:
                switch (c)
                {
                    case '{': case '[': case '(':
                        s = APERTURA_BRACKET;
                        push(pila,c);
                        break;

                    case '}': case ']': case ')':
                        if(atenderClausuraBracket(pila,c))
                            s = CLAUSURA_BRACKET;
                        else 
                            s = BRACKETS_NO_BALANCEADOS;
                        break;
                       
                    case '\'': 
                        s = APERTURA_COMILLAS_SIMPLES;
                        break;
                    
                    case '\"':
                        s = APERTURA_COMILLAS_DOBLES;
                        break;
     
                    default: //EOC
                        s = CARACTER_COMUN;
                }
                break;

            case CLAUSURA_BRACKET:
                switch (c)
                {
                    case '{': case '[': case '(':
                        s = APERTURA_BRACKET;
                        push(pila,c);
                        break;

                    case '}': case ']': case ')':
                        if(atenderClausuraBracket(pila,c))
                            s = CLAUSURA_BRACKET;
                        else 
                            s = BRACKETS_NO_BALANCEADOS;
                        break;

                    case '\'': 
                        s = APERTURA_COMILLAS_SIMPLES;
                        break;
                    
                    case '\"':
                        s = APERTURA_COMILLAS_DOBLES;
                        break;
      
                    default: //EOC
                        s = CARACTER_COMUN;
                }
                break;

            case APERTURA_COMILLAS_SIMPLES:
                switch (c)
                {
                    case '\\':
                        s = CARACTER_CONTRABARRA_COMILLA_SIMPLE;
                        break;

                    case '\'': case '\"':
                        s = ERROR_COMILLAS_DENTRO_DE_COMILLAS_SIMPLES;
                        break;

                    default:
                        s = CARACTER_COMILLAS_SIMPLES; 
                }               
                break;

        case CARACTER_COMILLAS_SIMPLES:
            switch (c)
            {
                case '\'':
                    s = CLAUSURA_COMILLAS_SIMPLES;
                    break;

                default: //EOC
                    s = ERROR_MAS_DE_UN_CARACTER_EN_COMILLAS_SIMPLES;
            }
            break;

        case CLAUSURA_COMILLAS_SIMPLES:
            switch (c)
            {
                case '\"':
                    s = APERTURA_COMILLAS_DOBLES;
                    break;

                case '\'':
                    s = APERTURA_COMILLAS_SIMPLES;
                    break;

                case '{': case '[': case '(':
                    s = APERTURA_BRACKET;
                    push(pila,c);
                    break;

                case '}': case ']': case ')':
                    if(atenderClausuraBracket(pila,c))
                        s = CLAUSURA_BRACKET;
                    else 
                        s = BRACKETS_NO_BALANCEADOS;
                    break;

                default: //EOC
                    s = CARACTER_COMUN;
            }
            break;

        case APERTURA_COMILLAS_DOBLES:
            switch (c)
            {
                case '\\':
                    s = CARACTER_CONTRABARRA_COMILLA_DOBLE;
                    break;

                case '\"':
                    s = CLAUSURA_COMILLAS_DOBLES;
                    break;

                default: //EOC
                    s = CARACTER_COMILLAS_DOBLES;
            }
            break;

        case CARACTER_COMILLAS_DOBLES:
            switch (c)
            {
                case '\\':
                    s = CARACTER_CONTRABARRA_COMILLA_DOBLE;
                    break;

                case '\"':
                    s = CLAUSURA_COMILLAS_DOBLES;
                    break;

                default: //EOC
                    s = CARACTER_COMILLAS_DOBLES;
            }
            break;

        case CLAUSURA_COMILLAS_DOBLES:
            switch (c)
            {
                case '\"':
                    s = APERTURA_COMILLAS_DOBLES;
                    break;

                case '\'':
                    s = APERTURA_COMILLAS_SIMPLES;
                    break;

                case '{': case '[': case '(':
                    s = APERTURA_BRACKET;
                    push(pila,c);
                    break;

                case '}': case ']': case ')':
                    if(atenderClausuraBracket(pila,c))
                        s = CLAUSURA_BRACKET;
                    else 
                        s = BRACKETS_NO_BALANCEADOS;
                    break;

                default: //EOC
                    s = CARACTER_COMUN;
            }
            break;

        case CARACTER_CONTRABARRA_COMILLA_SIMPLE:
            s = CARACTER_COMILLAS_SIMPLES;
            break;

        case CARACTER_CONTRABARRA_COMILLA_DOBLE:
            s = CARACTER_COMILLAS_DOBLES; 
            break;

        case BRACKETS_NO_BALANCEADOS:
            return -1; // Error por pila vacia o porque no cierra el bracket correcto

        case ERROR_MAS_DE_UN_CARACTER_EN_COMILLAS_SIMPLES:
            return -2;

        case ERROR_COMILLAS_DENTRO_DE_COMILLAS_SIMPLES:
            return -3;
        }
    }
    return 1;
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