#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

Token token;
bool tengoToken = false;

void ErrorSintactico()
{
    printf("Ocurrió un Error Sintáctico");
    exit(-1);   
}

void ErrorLexico()
{
    printf("Ocurrió un Error Lexico");
    exit(-1);   
}

void verificarToken()
{
    if (!tengoToken)
    { 
        GetNextToken(&token);
        tengoToken=true;
    }   
}

void GruposOpcionales()
{
    while(1)
    {
        verificarToken();

        // Deberiamos agregar los tengoToken=false para cada caso
        switch (token.type)
        {
        case Numeral: 
        case Comentario: 
        case Identificador: 
        case Punctuator: 
        case ConstNumerica: 
        case LitCadena: 
        case LParen: 
        case LBrack:
        case LBrace:
            Grupo();
            break;

        case LexError:
            ErrorLexico();
        
        default:
            return;
        }
    }
}

void TextosOpcionales()
{
    while(1)
    {
        verificarToken();
        
        // Deberiamos agregar los tengoToken=false para cada caso
        switch (token.type)
        {
        case Identificador: 
        case Punctuator: 
        case ConstNumerica: 
        case LitCadena: 
            Texto();
            break;

        case LexError:
            ErrorLexico();    
        
        default:
            return;
        }
    }
}

void Match (TokenType ttype)
{
    if(!tengoToken)
    GetNextToken(&token);
    
    if (ttype != token.type)       
        ErrorSintactico();     
}

#define largoMaxTextoReemplazo 100
#define largoMaxIdentifcador 100
void MatchTexto()
{    
    char *textoReemplazo = (char*)malloc(largoMaxTextoReemplazo);
    memset(textoReemplazo,'\0',sizeof(char) * largoMaxTextoReemplazo);   

    char *tokenInterno = (char*)malloc(largoMaxIdentifcador);
    memset(tokenInterno,'\0',sizeof(char) * largoMaxIdentifcador);

    tokenInterno = strcat(tokenInterno,token.val);
    
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
       
    set(tokenInterno, textoReemplazo);

    printf("\nTexto Reemplazo: %s",textoReemplazo);
}

void Texto()
{
    verificarToken();

    switch (token.type)
    {
    case Identificador:
        //Verificar id en la symbolTable
        //Imprimir lo que corresponda, el id si no esta, o el texto si esta
        TextosOpcionales();
        break;

    case Punctuator:
        //Imprimirlo
        TextosOpcionales();
        break;

    case ConstNumerica:
        //Imprimirlo
        TextosOpcionales();
        break;

    case LitCadena:
        //Imprimirlo
        TextosOpcionales();
        break;

    case LexError:
        ErrorLexico();
    
    default:
        break;
    }
}

void Directiva()
{
    verificarToken();

    switch (token.type)
    {
    case Define:
        tengoToken=false;
        Match(Identificador);
        MatchTexto(); //Aca se agrega a la symbolTable
        Match(NewLine);
        tengoToken=false;
        break;

    case Undefine:
        Match(Identificador);
        Match(NewLine);
        //Eliminar el id de la symbolTable
        break;

    case Include:
        tengoToken=false;
        Match(LitCadena);
        Match(NewLine);
        //Traer el archivo
        break;

    case Ifdef:
        Match(Identificador);
        //If id esta en la tabla de simbolos
        Match(NewLine);
        GruposOpcionales();
        //Hasta aca
        //else
        Match(Numeral);
        Match(Else);
        Match(NewLine);
        GruposOpcionales();
        //Hasta aca
        Match(Numeral);
        Match(Endif);
        Match(NewLine);
        break;

    case LexError:
        ErrorLexico();

    default:
        ErrorSintactico();
    }
}

void Grupo()
{
    verificarToken();

    switch (token.type)
    {
    case Comentario:
        printf(" ");
        tengoToken=false;
        break;
    
    case Numeral:
        tengoToken=false;
        Directiva();
        break;

    case Identificador: 
    case Punctuator: 
    case ConstNumerica: 
    case LitCadena:
        Texto();
        tengoToken=false;
        break;

    case LParen:
        GruposOpcionales();
        Match(RParen);
        tengoToken=false;
        break;

    case LBrack:
        GruposOpcionales(); 
        Match(RBrack);
        tengoToken=false;
        break;

    case LBrace:
        GruposOpcionales();
        Match(RBrace);
        tengoToken=false;
        break;

    case LexError:
        ErrorLexico();

    //Faltaria caso con New Line?

    default:
        ErrorSintactico();
    }
}

void ListaDeGrupos()
{
    Grupo();
    GruposOpcionales();
}

void UnidadDeTraduccion()
{
    ListaDeGrupos();
    Match(FDT);
}

int main ()
{
    UnidadDeTraduccion();
}




/*

-------------------------GRAMATICA----------------------------

<UnidadDeTraducción> -> <ListaDeGrupos> FDT

<ListaDeGrupos> -> <Grupo> <GruposOpcionales>

<GruposOpcionales> -> {<Grupo>}

Grupo -> 
    <Directiva>
    <Texto> 
    NewLine
    Comentario
    ( <GruposOpcionales> )
    [ <GruposOpcionales> ]
    { <GruposOpcionales> }
    
Directiva ->
    Numeral Define Identificador TextoReemplazo NewLine
    Numeral Undefine Identificador NewLine
    Numeral Include LitCadena NewLine
    Numeral Ifdef Identificador NewLine <GruposOpcionales> NewLine Numeral Else NewLine <GruposOpcionales> NewLine Numeral EndIf NewLine
 
 Texto ->
    Identifcador <TextosOpcionales>
    Punctuator <TextosOpcionales>
    ConstNumerica <TextosOpcionales>
    LitCadena <TextosOpcionales>

<TextosOpcionales> -> {<Texto>}
*/
