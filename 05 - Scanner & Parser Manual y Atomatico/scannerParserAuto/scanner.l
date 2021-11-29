%{
	#include <stdio.h>
    #include <string.h>
    #include "y.tab.h"

    extern YYSTYPE yylval;
%}

NUMERO		    [0-9]+
NUMERAL         #
PUNCTUATOR      [.&*+-;:!%<>=;]|==
IDENTIFICADOR   [_a-zA-Z][_a-zA-Z0-9]*

%option noyywrap

%%
[ \t]                   ;
\/\/[^\n]*				|
\/\*[^"*/"]*\*\/        {strcpy(yylval.strVal, yytext);return COMENTARIO;}
{NUMERAL}               {strcpy(yylval.strVal, yytext);return NUMERAL;}
define                  {strcpy(yylval.strVal, yytext);return DEFINE;}
undef                   {strcpy(yylval.strVal, yytext);return UNDEFINE;}
ifdef                   {strcpy(yylval.strVal, yytext);return IFDEF;}
else                    {strcpy(yylval.strVal, yytext);return ELSE;}
endif                   {strcpy(yylval.strVal, yytext);return ENDIF;}
include                 {strcpy(yylval.strVal, yytext);return INCLUDE;}
{NUMERO}    			|
{NUMERO}"."{NUMERO}		|
{NUMERO}?"."{NUMERO}	{strcpy(yylval.strVal, yytext);return CONSTNUMERICA;}
\n						{strcpy(yylval.strVal, yytext);return NEWLINE;}
{IDENTIFICADOR}         {strcpy(yylval.strVal, yytext);return IDENTIFICADOR;}
\(                      {strcpy(yylval.strVal, yytext);return LPAREN;}
\)                      {strcpy(yylval.strVal, yytext);return RPAREN;} 
\[                      {strcpy(yylval.strVal, yytext);return LBRACKET;} 
\]                      {strcpy(yylval.strVal, yytext);return RBRACKET;} 
\{                      {strcpy(yylval.strVal, yytext);return LBRACE;}
\}                      {strcpy(yylval.strVal, yytext);return RBRACE;}
{PUNCTUATOR}            {strcpy(yylval.strVal, yytext);return PUNCTUATOR;}
.                       {printf("\nHubo un error lexico con: %s\n",yytext);exit(0);}
\"[^\n\"]*\"            {strcpy(yylval.strVal, yytext);return LITCADENA;}
<<EOF>>				    return FDT;
%%

