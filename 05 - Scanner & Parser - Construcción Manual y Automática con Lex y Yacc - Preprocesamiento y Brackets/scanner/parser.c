#include "scanner.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

Token token;
void ErrorSintactico();
void Grupo();


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

void Match (TokenType ttype){
    
    GetNextToken(&token);
    printf("\n%s\t%s",stringTokenType(token.type),token.val);

    if (ttype != token.type)       
        ErrorSintactico();   
            
}

/*
Comentario
 Directiva
 GrupoIf
 Texto
 ( Grupo )
 [ Grupo ]
 { Grupo }
*/
#define largoMaxTextoReemplazo 100
void MatchTexto()
{    
    char *textoReemplazo = (char*)malloc(largoMaxTextoReemplazo);
    memset(textoReemplazo,'\0',sizeof(char) * largoMaxTextoReemplazo);
    
    do{
        GetNextToken(&token);
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
        if(token.type == LexError || token.type == FDT)
            ErrorSintactico();
        else
        {
            if(token.val)
            {
                textoReemplazo = strcat(textoReemplazo,token.val);
                textoReemplazo = strcat(textoReemplazo," ");
            }
        }
    } while(token.type != NewLine);

    printf("\nTexto Reemplazo: %s",textoReemplazo);
    //Guardar texto reemplazo en symboltable
}

void Directiva(){      
    GetNextToken(&token);
    switch (token.type)
    {
    case Define:        
        Match(Identificador);
        //#define MAX MIN 10\n        
        MatchTexto();
        //Match(TextoReemplazo);        
        //Match(NewLine);
        break;

    case Undefine:       
        Match(Identificador);           
        Match(NewLine);
        break;

    case Include:        
        Match(LitCadena);        
        Match(NewLine);
        break;
    
    case Ifdef:        
        Match(Identificador);        
        Match(NewLine);
        //GetNextToken(&token);
        Grupo();
        Match(NewLine);        
        Match(Numeral);       
        Match(Endif);        
        Match(NewLine);
        break;

    case LexError:
        printf("Hay un error léxico");
        exit(-1);
    
    default:
        ErrorSintactico();       
    }

}

/*
 Texto ->
    Identificador
    Punctuator
    ConstNumerica
    Texto Identificador
    Texto Punctuator   
    Texto ConstNumerica
    */
   /*
   int a = 5; //
Texto
Identificador Texto
Identificador Identificador Texto
Identificador Identificado Punctuator Texto
Identificador Identificado Punctuator ConstNumerica Texto
Identificador Identificado Punctuator ConstNumerica Texto
*/


//TODO: Estamos leyendo un token al final, que estamos perdiendo porque se pisa con uno nuevo.
void Texto(){    
    if (token.type == Identificador || token.type == Punctuator || token.type == ConstNumerica){        
        GetNextToken(&token);
        Texto();
     } 
}

/*
Grupo ->
    Directiva
    Comentario
    Texto
    ( Grupo )
    [ Grupo ]
    { Grupo }
*/
void Grupo(){    
    printf("\nEntro a Grupo");
    GetNextToken(&token);
    printf("\n%s\t%s",stringTokenType(token.type),token.val);
    switch (token.type)
    {
    case Comentario:
        break;

    case Numeral:
        Directiva();
        break;

    case Identificador: case Punctuator: case ConstNumerica:
        Texto();
        break;
  
    case LParen:
        //GetNextToken(&token);
        Grupo();        
        Match(RParen);
        break;

    case LBrack:
        //GetNextToken(&token);
        Grupo();        
        Match(RBrack);
        break;

    case LBrace:
        //GetNextToken(&token);
        Grupo();        
        Match(RBrace);
        break;

    case LexError:
        printf("Hay un error léxico");
        exit(-1);
    
    default:
        ErrorSintactico();
    }

}


/*
UnidadDeTraducción ->
 Grupo FDT |
 Grupo UnidadDeTraducción
*/

void UnidadDeTraduccion(){    
    printf("\nEntro a Unidad de Traduccion");
    Grupo();
     
    GetNextToken(&token);
    printf("\n%s\t%s",stringTokenType(token.type),token.val);
    switch(token.type)
    {
        case FDT:
            printf("Está todo bien");
            break;

        case LexError:
            printf("Hay un error léxico");
            break;

        default:
            UnidadDeTraduccion();
    }
}

void ErrorSintactico(){
    printf("Ocurrió un Error Sintáctico");
    exit(-1);   
}


int main (){
    
    //UnidadDeTraduccion();
    
    while(GetNextToken(&token))
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
    
    printf("\n%s\t\t%s",stringTokenType(token.type),token.val);
    printf("\n");
    
}
/*
void Grupo2(){    
    printf("\nEntro a Grupo");
    GetNextToken(&token);
    printf("\n%s\t%s",stringTokenType(token.type),token.val);
    switch (token.type)
    {
    case Comentario:
        break;

    case Numeral:
        Directiva();
        break;

    case Identificador: case Punctuator: case ConstNumerica:
        Texto();
        break;
  
    case LParen:
        //GetNextToken(&token);
        Grupo();        
        Match(RParen);
        break;

    case LBrack:
        //GetNextToken(&token);
        Grupo();        
        Match(RBrack);
        break;

    case LBrace:
        //GetNextToken(&token);
        Grupo();        
        Match(RBrace);
        break;

    case LexError:
        printf("Hay un error léxico");
        exit(-1);
    
    default:
        ErrorSintactico();
    }

}

void ListaDeGrupos()
{
    Grupo2();
    while(1)
    {
        GetNextToken(&token);
        switch (token.type)
        {
            case :
                break;
        
            default:
                break;
        }
        
    }
}

void UnidadDeTraduccion2()
{    
    ListaDeGrupos();
    Match(FDT);    
}

int main()
{
    UnidadDeTraduccion2();
}*/

/*Version 2

UnidadDeTraducción -> <ListaDeGrupos> FDT

ListaDeGrupos -> <Grupo> {<Grupo>}

Grupo -> 
    <Directiva>
    Comentario
    <Texto>
    ( <Grupo> )
    [ <Grupo> ]
    { <Grupo> }

Directiva ->
    Numeral Define Identificador TextoReemplazo NewLine
    Numeral Undefine Identificador NewLine
    Numeral Include LitCadena NewLine
    Numeral Ifdef Identificador NewLine <Grupo> NewLine Numeral EndIf NewLine
 
 Texto ->
    Identifcador
    Punctuator
    ConstNumerica
    Identificador <Texto>
    Punctuator <Texto>   
    ConstNumerica <Texto>

TODO: Consultar por token identificador, es texto o token?
TODO: Consultar por el Else del ifdef. 

*/


/*

UnidadDeTraducción ->
 Grupo FDT |
 Grupo UnidadDeTraducción

Grupo ->
    Directiva
    Comentario
    Texto
    ( Grupo )
    [ Grupo ]
    { Grupo }

Directiva ->
    Numeral Define Identificador TEXTODEREEMPLAZO NewLine
    Numeral Undefine Identificador NewLine
    Numeral Include LitCadena NewLine
    Numeral Ifdef Identificador NewLine Grupo NewLine Numeral EndIf NewLine
 
 Texto ->
    Identifcador
    Punctuator
    ConstNumerica
    Texto Identificador
    Texto Punctuator   
    Texto ConstNumerica

TODO: Consultar por token identificador, es texto o token?
TODO: Consultar por el Else del ifdef. 

 */