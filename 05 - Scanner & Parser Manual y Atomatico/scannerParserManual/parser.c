#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "../preprocessorSymbolTable/preprocessorSymbolTable.h"
#include "../defineSymbolTable/defineSymbolTable.h"

Token token;
bool tengoToken = false;
const char* textoReemplazo;

char *strdup (const char*);

void ErrorSintactico();
void ErrorLexico();
void verificarToken();
void imprimirIdentificador();
void GruposOpcionales();
void TextosOpcionales();
void Match (TokenType);
void MatchTexto();
static void traerArchivoInclude(char*);
void Texto();
void Directiva();
void Grupo();
void ListaDeGrupos();
void UnidadDeTraduccion();

void GruposOpcionalesDirectiva();
void leerTokenHastaNumeral();




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

    case Identificador:
        return "(Identificador)";

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

void imprimirIdentificador(){
    IdType tipoToken = getPrep(token.val);    
      
    if ( tipoToken != idDefine){           
        printf("%s ",token.val);
    } else {            
        textoReemplazo = get(token.val);
        printf("%s ",textoReemplazo);
    }
}

void GruposOpcionales()
{
    while(1)
    {
        verificarToken();

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
        case NewLine:
            Grupo();
            break;

        case LexError:
            ErrorLexico();
        
        default:
            return;
        }
    }
}

void GruposOpcionalesDirectiva()
{
    while(1)
    {
        verificarToken();

        switch (token.type)
        {        
        case Comentario: 
        case Identificador: 
        case Punctuator: 
        case ConstNumerica: 
        case LitCadena: 
        case LParen: 
        case LBrack:
        case LBrace:
        case NewLine:
            Grupo();
            break;

        case LexError:
            ErrorLexico();
        
        default:
            return;
        }
    }
}

void leerTokenHastaNumeral()
{
    verificarToken();

    while(token.type != Numeral)
    {
        tengoToken=false;
        verificarToken();
    }    
}

void TextosOpcionales()
{
    while(1)
    {
        
        verificarToken();
        
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

}


static void traerArchivoInclude(char *path)
{
    int nc;
    FILE *arch = fopen (path, "r");
    if (arch == NULL)
    {
        printf("No existe el archivo");
        exit(-1);
    }
    else
    {
        while ((nc = fgetc(arch))!= EOF)
            putchar(nc);

        fclose(arch);
        printf("\n");
    }
}

void Texto()
{
    verificarToken();

    switch (token.type)
    {
    case Identificador:
        imprimirIdentificador();
        tengoToken = false;
        TextosOpcionales();
        break;

    case Punctuator:
        printf("%s",token.val);
        tengoToken = false;
        TextosOpcionales();
        break;

    case ConstNumerica:
        printf("%s",token.val);
        tengoToken = false;
        TextosOpcionales();
        break;

    case LitCadena:
        printf("\"%s\"",token.val);
        tengoToken = false;
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
        setPrep(token.val, idDefine); 
        MatchTexto(); 
        tengoToken=false;
        break;

    case Undefine:
        tengoToken = false;          
        Match(Identificador);
        deletePrep(token.val);
        delete(token.val); 
        Match(NewLine);    
        tengoToken=false;    
        break;

    case Include:
        tengoToken=false;
        Match(LitCadena);
        char *path = strdup(token.val);
        Match(NewLine);
        traerArchivoInclude(path);
        tengoToken=false; 
        break;

    case Ifdef:
        tengoToken = false;

        Match(Identificador);
        if (getPrep(token.val) == idDefine){            
            GruposOpcionalesDirectiva();            
            tengoToken = false;                
            leerTokenHastaNumeral();
        }else{
            leerTokenHastaNumeral();
            Match(Numeral);
            tengoToken = false;
            Match(Else);
            tengoToken = false;
            Match(NewLine);
            GruposOpcionalesDirectiva(); 
        }       
        tengoToken = true;
        Match(Numeral);
        tengoToken = false;
        Match(Endif);
        tengoToken = false;

        Match(NewLine);
        tengoToken=false; 
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
        
        break;

    case LParen:
        printf("(");
        tengoToken = false;
        GruposOpcionales();
        Match(RParen);
        printf(")");
        tengoToken=false;
        break;

    case LBrack:
        printf("[");
        tengoToken = false;
        GruposOpcionales(); 
        Match(RBrack);
        printf("]");
        tengoToken=false;
        break;

    case LBrace:
        printf("{");
        tengoToken = false;
        GruposOpcionales();
        Match(RBrace);
        printf("}");
        tengoToken=false;
        break;

    case LexError:
        ErrorLexico();

    case NewLine:
        printf("\n");
        tengoToken = false;
        break;    

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
    
    setPrep("define",idReservado);
    setPrep("undef",idReservado);
    setPrep("ifdef",idReservado);
    setPrep("else",idReservado);
    setPrep("endif",idReservado);
    setPrep("include",idReservado);
    /*
while(GetNextToken(&token))
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
    
    printf("\n%s\t\t%s",stringTokenType(token.type),token.val);
    printf("\n");
*/
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
    Numeral Ifdef Identificador NewLine <GruposOpcionalesDirectiva> NewLine Numeral Else NewLine <GruposOpcionalesDirectiva> NewLine Numeral EndIf NewLine
 
<GruposOpcionalesDirectiva> -> {<GruposDirectiva>}

GrupoDirectiva -> 
    <Texto> 
    NewLine
    Comentario
    ( <GruposOpcionalesDirectiva> )
    [ <GruposOpcionalesDirectiva> ]
    { <GruposOpcionalesDirectiva> }

 Texto ->
    Identifcador <TextosOpcionales>
    Punctuator <TextosOpcionales>
    ConstNumerica <TextosOpcionales>
    LitCadena <TextosOpcionales>

<TextosOpcionales> -> {<Texto>}
*/
