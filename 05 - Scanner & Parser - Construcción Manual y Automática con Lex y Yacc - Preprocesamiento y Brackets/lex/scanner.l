%{
	#include <stdio.h>
    #include <string.h>
    #include "y.tab.h"

	typedef enum {
    Comentario,
    Numeral,
    Define,
    Undefine,
    Ifdef,
    Else,
    Endif,
    Include,
    Identificador,
    LParen='(', 
    RParen=')', 
    LBrack='[', 
    RBrack=']', 
    LBrace='{', 
    RBrace='}', 
    Punctuator, 
    LexError,
    LitCadena,
    NewLine,
    ConstNumerica,
    Fdt
	} TokenType;

    extern YYSTYPE yyval;
%}

NUMERO		    [0-9]+
NUMERAL         #
PUNCTUATOR      [.&*+-;:!%<>=;]|==
IDENTIFICADOR   [_a-zA-Z][_a-zA-Z0-9]*

%option noyywrap

%%
[ \t]                   ;
\/\/[^\n]*				|
\/\*[^"*/"]*\*\/        return Comentario;
{NUMERAL}               return Numeral;
define                  return Define;
undef                   return Undefine;
ifdef                   return Ifdef;
else                    return Else;
endif                   return Endif;
include                 return Include;
{NUMERO}    			|
{NUMERO}"."{NUMERO}		|
{NUMERO}?"."{NUMERO}	return ConstNumerica;
\n						return NewLine;
{IDENTIFICADOR}         {strcpy(yylval.strVal, yytext);return Identificador;}
\(                      return LParen; 
\)                      return RParen; 
\[                      return LBrack; 
\]                      return RBrack; 
\{                      return LBrace; 
\}                      return RBrace;
{PUNCTUATOR}            return Punctuator;
.                       {printf("\nHubo un error lexico con: %s\n",yytext);exit(0);}
\"[^\n\"]*\"            return LitCadena;
<<EOF>>				    return Fdt;
%%

char* stringTokenType(TokenType);

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

    case Else:
        return "(Else)";

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

    case Fdt:
        return "(Fdt)";

    default: // No deberia pasar
        return "Error, no deberia haber llegado aca";
    }
}
