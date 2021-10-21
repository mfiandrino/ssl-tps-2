#include "scanner.h"
#include <stdio.h>

Token token;

//TODO: Analizar si se puede implementar 
//int (*fun_ptr)(Token token);


char* stringTokenType(TokenType tokTyp)
{
    switch (tokTyp)
    {
    case Comentario:
        return "(Comentario)";

    case Numeral:
        return "(Numeral)";

    case Define:
        return "(Define)";
    
    case Undefine:
        return "(Undefine)";

    case Ifdef:
        return "(Ifdef)";

    case Endif:
        return "(Endif)";

    case Include:
        return "(Include)";

    case Path:
        return "(Path)";

    case Identificador:
        return "(Identificador)";

    case TextoReemplazo:
        return "(TextoReemp)";

    case LParen:
        return "(LParen)";

    case RParen:
        return "(RParen)";

    case LBrack:
        return "(LBrack)";

    case RBrack:
        return "(RBrack)";
    
    case LBrace:
        return "(LBrace)";

    case RBrace:
        return "(RBrace)";

    case Punctuator:
        return "(Punctuator)";

    case LexError:
        return "(LexError)";

    case LitCadena:
        return "(LitCadena)";

    case NewLine:
        return "(NewLine)";

    case ConstNumerica:
        return "(ConstNumerica)";

    case FDT:
        return "(FDT)";

    default: // No deberia pasar
        return "Error, no deberia haber llegado aca";
    }
}

void Match (Token tokenEsperado){

    Token t;
    GetNextToken(&t);

    if (strcmp(t.type, tokenEsperado.type) == 0){
        //TODO: Falta utilizar esta variable mas adelante  
        token.type = t.type;
        token.val = t.val;
    }else{
        ErrorSintactico();
    }
}

void TokenNumeral (void){
    GetNextToken(&token);
    switch(token.type){
        case Define:
            TokenDefine();
        break;
        case Undefine:
            TokenUndefine();
        break;            
        case Ifdef:
            TokenIfdef();
        break;
        case Endif:
            TokenEndif();
        break;
        case Include:
            TokenInclude();
        break;
        default:
            ErrorSintactico();
    }
}

void TokenDefine (void){

    Token t;
    t.type = Identificador;
    Match(t);

    TokenIdentificadorDefine();

}

void TokenIdentificadorNumeral (void) {

    Token t;
    t.type = NewLine;
    Match(t);

}


void TokenIdentificadorDefine (void){    

    Token t;
    t.type = TextoReemplazo;
    Match(t);

    TokenTextoReemplazo();   
}

void TokenTextoReemplazo (void){   

    Token t;
    t.type = NewLine;
    Match(t);

}


//Asumimos que despues de un comentario hay un NewLine
void TokenComentario (void){    
    Token t;
    t.type = NewLine;
    Match(t);
}

//Consultar: Podemos asumir que un undef siempre termina con un newLine?
void TokenUndefine (void){
    Token t;
    t.type = Identificador;
    Match(t);

    TokenIdentificadorNumeral();        
}

void TokenInclude (void){
    Token t;
    t.type = Path;
    Match(t);   

    TokenPath(); 
}

void TokenPath (void){
    Token t;
    t.type = NewLine;
    Match(t);                  
}

void TokenIfdef (void){
    Token t;
    t.type = Identificador;
    Match(t);

    TokenIdentificadorNumeral();        
}

void TokenEndif (void){
    Token t;
    t.type = NewLine;
    Match(t);
}

void TokenIdentificador(void){ 
    GetNextToken(&token);
    switch(token.type){
        case Identificador:
            TokenIdentificador();
        break;
        case Punctuator:
            TokenPunctuator();
        break;
        case LParen:
            TokenLParen();
        break;
        case RParen:
            TokenRParen();
        break;
        case LBrack:
            TokenLBrack();
        break;
        case RBrack:
            TokenRBrack();
        break;
        case LBrace:
            TokenLBrace();
        break;
        case RBrace:
            TokenRBrace();
        break;
        case Comentario:
            TokenComentario();
        break;
        case NewLine: break;
        default:
            ErrorSintactico();
    }
}

void TokenPunctuator(void){ 
    GetNextToken(&token);
    switch(token.type){
        case Comentario:
            TokenComentario();
        break;
        case Punctuator:
            TokenPunctuator();
        break;
        case LitCadena:
            TokenLitCadena();
        break;
        case ConstNumerica:
            TokenConstNumerica();
        break;
        case RParen:
            TokenRParen();
        break;
        case RBrack:
            TokenRBrack();
        break;
        case RBrace:
            TokenRBrace();
        break;
        case NewLine: break;
        default:
            ErrorSintactico();
    }    
}

void TokenLitCadena(void){
    GetNextToken(&token);
    switch (token.type){
    case Punctuator:
    case Comentario:
    case RParen:
    case RBrack:
    default:
    }
}

void TokenConstNumerica(void){
    GetNextToken(&token);
    switch (token.type){
    case Punctuator:
    case Comentario:
    case RParen:
    case RBrack:
    default:
    }
}

void TokenLParen(void){
    GetNextToken(&token);
    switch (token.type){
    case Identificador:
    case LitCadena:
    case ConstNumerica:
    case RParen:
    case Comentario:
    case Punctuator:
    case NewLine:
    default:
    }

}

void ErrorSintactico(){
    printf("Ocurrió un Error Sintáctico");
    //TODO: CORTAR LA EJECUCION
}


int main (){
    while(GetNextToken(&token)){
        
        switch (token.type){
            case Numeral:
                TokenNumeral();
            break;
            case Comentario:
                TokenComentario();
            break;
            case Identificador:
                TokenIdentificador();
            break;
            default:               

        }
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
    }
    printf("\n%s\t\t%s",stringTokenType(token.type),token.val);
    printf("\n");
}



/*

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


*/