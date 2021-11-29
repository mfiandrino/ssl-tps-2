%{
	#include <stdio.h>
    #include <string.h>

    typedef enum {
    COMENTARIO,
    NUMERAL,
    DEFINE,
    UNDEFINE,
    IFDEF,
    ELSE,
    ENDIF,
    INCLUDE,
    IDENTIFICADOR,
    LPAREN, 
    RPAREN, 
    LBRACKET, 
    RBRACKET, 
    LBRACE, 
    RBRACE, 
    PUNCTUATOR, 
    LITCADENA,
    NEWLINE,
    CONSTNUMERICA,
    FDT
	} TokenType;
%}

NUMERO		    [0-9]+
NUMERAL         #
PUNCTUATOR      [.&*+-;:!%<>=;]|==
IDENTIFICADOR   [_a-zA-Z][_a-zA-Z0-9]*

%option noyywrap

%%
[ \t]                   ;
\/\/[^\n]*				|
\/\*[^"*/"]*\*\/        return COMENTARIO;
{NUMERAL}               return NUMERAL;
define                  return DEFINE;
undef                   return UNDEFINE;
ifdef                   return IFDEF;
else                    return ELSE;
endif                   return ENDIF;
include                 return INCLUDE;
{NUMERO}    			|
{NUMERO}"."{NUMERO}		|
{NUMERO}?"."{NUMERO}	return CONSTNUMERICA;
\n						return NEWLINE;
{IDENTIFICADOR}         return IDENTIFICADOR;
\(                      return LPAREN;
\)                      return RPAREN;
\[                      return LBRACKET;
\]                      return RBRACKET;
\{                      return LBRACE;
\}                      return RBRACE;
{PUNCTUATOR}            return PUNCTUATOR;
.                       {printf("\nHubo un error lexico con: %s\n",yytext);exit(0);}
\"[^\n\"]*\"            return LITCADENA;
<<EOF>>				    return FDT;
%%


char* stringTokenType(TokenType tokTyp);

int main()
{
    int token;
	while((token = yylex()) != FDT)
        printf("\n%s\t%s",stringTokenType(token),yytext);
    printf("\n%s\t%s",stringTokenType(token),yytext);
}

char* stringTokenType(TokenType tokTyp)
{
    switch (tokTyp)
    {
    case COMENTARIO:
        return "(Comentario)";

    case NUMERAL:
        return "(Numeral)";

    case DEFINE:
        return "(Define)";
    
    case UNDEFINE:
        return "(Undefine)";

    case IFDEF:
        return "(Ifdef)";

    case ELSE:
        return "(Else)";
        
    case ENDIF:
        return "(Endif)";

    case INCLUDE:
        return "(Include)";

    case IDENTIFICADOR:
        return "(Identificador)";

    case LPAREN:
        return "(LParen)";

    case RPAREN:
        return "(RParen)";

    case LBRACKET:
        return "(LBrack)";

    case RBRACKET:
        return "(RBrack)";
    
    case LBRACE:
        return "(LBrace)";

    case RBRACE:
        return "(RBrace)";

    case PUNCTUATOR:
        return "(Punctuator)";

    case LITCADENA:
        return "(LitCadena)";

    case NEWLINE:
        return "(NewLine)";

    case CONSTNUMERICA:
        return "(ConstNumerica)";

    case FDT:
        return "(FDT)";

    default: // No deberia pasar
        return "Error, no deberia haber llegado aca";
    }
}




