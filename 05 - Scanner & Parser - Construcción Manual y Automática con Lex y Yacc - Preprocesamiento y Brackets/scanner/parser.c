#include "scanner.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../preprocessorSymbolTable/preprocessorSymbolTable.h"
#include "../defineSymbolTable/defineSymbolTable.h"

bool tengoToken = false;
bool puedoImprimir = false;
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
    
    Token tokenInterno = token;


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

    set(tokenInterno.val, textoReemplazo);

    printf("\nTexto Reemplazo: %s",textoReemplazo);
    //Guardar texto reemplazo en symboltable
}

void Directiva(){
    if (!tengoToken){      
        GetNextToken(&token);   
        tengoToken = true;
    } 
    switch (token.type)
    {
    case Define:                
        Match(Identificador);
        setPrep(token.val, idDefine);               
        MatchTexto();
        tengoToken = false;
        break;

    case Undefine:       
        Match(Identificador);
        deletePrep(token.val);
        delete(token.val);         
        Match(NewLine);
        tengoToken = false;
        break;

    case Include:        
        Match(LitCadena);        
        Match(NewLine);
        //agregar funcion para traer el archivo
        tengoToken = false;
        break;
    
    case Ifdef:        
        Match(Identificador);       
        if (getPrep(token.val)==idDefine)
            // imprimir hasta #else o #endif
        Match(NewLine);
        tengoToken = false;
        //GetNextToken(&token);
        //agregar flag para definir si imprimimos o no
        Grupo();
        Match(NewLine); 
        /* Match(Numeral);
        Match(Else);
        Grupo();
        Match(NewLine); 
        tengoToken = false; */     //CHEQUEAR SI ESTO ES CORRECTO O NO HAY ELSE  
        Match(Numeral);       
        Match(Endif);        
        Match(NewLine);
        tengoToken = false;
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

void Texto(){

    if (token.type == Identificador || token.type == Punctuator || token.type == ConstNumerica){        
        if (token.type == Identificador){
            const char* textoAReemplazar = get(token.val);
            if (textoAReemplazar != NULL){
                 //printf(textoAReemplazar, "\n");
                 printf("\n%s\t%s",stringTokenType(token.type),token.val);
            }     
            else if(puedoImprimir){
                printf("\n%s\t%s",stringTokenType(token.type),token.val);
            }
        }
        else{
           // printf(token.val, "\n");
            printf("\n%s\t%s",stringTokenType(token.type),token.val);
            }
            
        GetNextToken(&token);
        puedoImprimir = true;
        //printf("\n%s\t%s",stringTokenType(token.type),token.val);
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
    printf("\n----------------Entro a Grupo----------------");

    if(!tengoToken){
        GetNextToken(&token);
        tengoToken = true;
    }

    printf("\n%s\t%s",stringTokenType(token.type),token.val); 
    if (token.val == "["){
        printf("ENCONTRE UN CORCHETE");
    }

    //TODO: Revisar caso de los brackts
      
    switch (token.type)
    {
    case Comentario:
        printf(" ");
        tengoToken = false;
        break;

    case Numeral:
        tengoToken = false;
        Directiva();        
        break;

    case Identificador: case Punctuator: case ConstNumerica:
        puedoImprimir = false;         
        Texto();
        printf("\n%s\t%s",stringTokenType(token.type),token.val); //Imprimos el NewLine, sino lo perdemos
        tengoToken = false;
        break;
  
    case LParen:
        tengoToken = true;
        printf("\n%s\t%s",stringTokenType(token.type),"(");
        Grupo();        
        Match(RParen);
        printf("\n%s\t%s",stringTokenType(token.type),")");
        tengoToken = false;
        break;

    case LBrack:
        tengoToken = true;
        printf("Prueba2");
        printf("\n%s\t%s",stringTokenType(token.type),"[");
        Grupo();        
        Match(RBrack);
        printf("\n%s\t%s",stringTokenType(token.type),"]");
        tengoToken = false;
        break;

    case LBrace:
        tengoToken = true;
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
        Grupo();        
        Match(RBrace);
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
        tengoToken = false;
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
    printf("\n--------------Entro a Unidad de Traduccion----------------");

    Grupo();

    if(!tengoToken){
        GetNextToken(&token);
        tengoToken = true;
    }
    
    //printf("\n%s\t%s",stringTokenType(token.type),token.val);

    switch(token.type)
    {
        case FDT:
            printf("Llegamos al token FDT");
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
    setPrep("define",idReservado);
    setPrep("undef",idReservado);
    setPrep("ifdef",idReservado);
    setPrep("else",idReservado);
    setPrep("endif",idReservado);
    setPrep("include",idReservado);

    UnidadDeTraduccion();
    /*
    while(GetNextToken(&token))
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
    
    printf("\n%s\t\t%s",stringTokenType(token.type),token.val);
    printf("\n");*/
    
}
/*
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