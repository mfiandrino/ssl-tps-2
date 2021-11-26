%{
	#include <stdio.h>
	#include "y.tab.h"
	void yyerror(char *);
%}

%option noyywrap

NUMERO				[0-9]+
NUMERAL				\#
DEFINE				define
UNDEF               undef
INCLUDE             include
IFDEF               ifdef
ELSE                else
ENDIF               endif
PUNTO_Y_COMA		[";"]
INICIO_COMENTARIO	["/*""//"]
FIN_COMENTARIO		["*/""\n"]
LETRA				[a-zA-Z]
GUIONES				[-_]
LPAREN              ["("]
LBRACK              ["["]
LBRACE              ["{"]
 
IDENTIFICADOR		{LETRA}({LETRA}|{NUMERO}|{GUIONES})*
TEXTOREEMPLAZO		({NUMERO}|{LETRA}|" ")+$