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
        printf("\nToken pedido:");
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
        tengoToken=true;
    }   
}

void imprimirIdentificador(){
    IdType tipoToken = getPrep(token.val);    
      
    if ( tipoToken != idDefine){           
        printf("\n%s\t%s",stringTokenType(token.type),token.val);            
    } else {            
        textoReemplazo = get(token.val);
        printf("\n%s\t%s",stringTokenType(token.type),textoReemplazo);
    }
}

void GruposOpcionales()
{
    printf("\nEntro a GruposOpcionales\n");
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

void TextosOpcionales()
{
    printf("\nEntro a TextosOpcionales\n");
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
            printf("\nEntro al default de textos opcionales\n");
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


static void traerArchivoInclude(char *path)
{
    printf("\nEntro a traerArchivoInclude\n");
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
    }
}

void Texto()
{
    printf("\nEntro a Texto\n");
    verificarToken();

    switch (token.type)
    {
    case Identificador:
        imprimirIdentificador();
        tengoToken = false;
        TextosOpcionales();
        break;

    case Punctuator:
        //printf(token.val);
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
        tengoToken = false;
        TextosOpcionales();
        break;

    case ConstNumerica:
        //printf(token.val);
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
        tengoToken = false;
        TextosOpcionales();
        break;

    case LitCadena:
        //printf(token.val);
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
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
    printf("\nEntro a Directiva\n");
    verificarToken();

    switch (token.type)
    {
    case Define:
        tengoToken=false;
        Match(Identificador);
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
        setPrep(token.val, idDefine); 
        MatchTexto(); 
        //Match(NewLine);
        tengoToken=false;
        break;

    case Undefine:
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
        //free(path);
        tengoToken=false; 
        break;

    case Ifdef:
        printf("\n%s\t%s",stringTokenType(token.type),token.val);
        tengoToken = false;
        Match(Identificador);
        //Si el id esta en la tabla de simbolos
        if (getPrep(token.val) == idDefine){            
            Match(NewLine);
            GruposOpcionales();
            Match(NewLine);                
           // leerTokenHastaNumeral();
        }else{
           // leerTokenHastaNumeral();
            Match(Numeral);
            Match(Else);
            Match(NewLine);
            GruposOpcionales();
            Match(NewLine);
        }       
        tengoToken=false;  
        //leerTokenHastaNumeral();
        Match(Numeral);
        Match(Endif);
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
    printf("\nEntro a Grupo\n");
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
    printf("\nEntro a ListaDeGrupos\n");
    Grupo();
    GruposOpcionales();
}

void UnidadDeTraduccion()
{
    printf("\nEntro a UnidadDeTraduccion\n");
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
