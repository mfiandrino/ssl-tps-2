%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>	
	#include "scanner.h"
%}

%option noyywrap

%%

\#	return Numeral; // TODO: Falta hacer el comentario 
"define"	return Define;
"undef"	return Undef;
"ifdef"	return Ifdef;
"else"	return Else;
"endif"	return Endif;
"include"	return Include;
"=="	return Punctuator;
[.&*+-;:!%<>=;]	return Punctuator; 
[a-zA-Z0-9] return Identificador;
\n return Newline;
\(	return LParen;              
"["	return LBrack;             
"{"	return LBrace;              
")"	return RParen;
"]"	return RBrack;              
"}"	return RBrace;  
[0-9]+    {yylval.intVal=atoi(yytext);return ConstNumerica;}
[_-a-zA-Z]*	{strcpy(yylval.strVal, yytext);return Identificador;}
<<EOF>> return FDT;
.	return LexError;
( \/ \/(.)\n | \/ \* ( . | \n) \* \/ ) 	return Comentario; 	          

%%


int GetNextToken(){
	return yylex();
}