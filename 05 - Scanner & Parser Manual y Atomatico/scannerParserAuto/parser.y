%{
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>     
    #include "../preprocessorSymbolTable/preprocessorSymbolTable.h"
    #include "../defineSymbolTable/defineSymbolTable.h"
   
    
    int yylex(void);
    void yyerror(char const *);
    //#define YYSTYPE char*
%}

%union{
    char strVal[100];
}

%token <strVal> LPAREN
%token <strVal> RPAREN
%token <strVal> LBRACKET
%token <strVal> RBRACKET
%token <strVal> LBRACE
%token <strVal> RBRACE
%token <strVal> NEWLINE
%token <strVal> COMENTARIO
%token <strVal> NUMERAL
%token <strVal> DEFINE
%token <strVal> IDENTIFICADOR
%token <strVal> TEXTOREEMPLAZO
%token <strVal> UNDEFINE
%token <strVal> INCLUDE
%token <strVal> LITCADENA
%token <strVal> IFDEF
%token <strVal> ELSE
%token <strVal> ENDIF
%token <strVal> PUNCTUATOR
%token <strVal> CONSTNUMERICA
%token <strVal> FDT 0

%type <strVal> unidadDeTraduccion
%type <strVal> grupo
%type <strVal>  directiva
%type <strVal> texto
%type <strVal> gruposOpcionesDirectiva
%%

unidadDeTraduccion: grupo FDT {printf("%s",$2);}

grupo: 
    directiva
|   texto 
|   NEWLINE {printf("\nNewline: %s",$1);}
|   COMENTARIO {printf("\nComentario: ");}
|   grupo directiva 
|   grupo texto 
|   grupo NEWLINE  {printf("\nNewline: %s",$1);}
|   grupo COMENTARIO  {printf("\nComentario: ");}
|   LPAREN grupo RPAREN {printf("\n%s %s",$1,$3);}
|   LBRACKET grupo RBRACKET {printf("\n%s  %s",$1,$3);}
|   LBRACE grupo RBRACE {printf("\n%s  %s",$1,$3);}
;

directiva:  
    NUMERAL DEFINE IDENTIFICADOR CONSTNUMERICA NEWLINE  {printf("\n%s  %s  %s  %s  %s",$1,$2,$3,$4,$5);}
|   NUMERAL UNDEFINE IDENTIFICADOR NEWLINE              {printf("\n%s  %s  %s  %s",$1,$2,$3,$4);}
|   NUMERAL INCLUDE LITCADENA NEWLINE                   {printf("\n%s  %s  %s  %s",$1,$2,$3,$4);}
|   NUMERAL IFDEF IDENTIFICADOR NEWLINE gruposOpcionesDirectiva NEWLINE NUMERAL ELSE NEWLINE gruposOpcionesDirectiva NEWLINE NUMERAL ENDIF NEWLINE
;

gruposOpcionesDirectiva:
    texto 
|   NEWLINE {printf("\nNewline: %s",$1);}
|   COMENTARIO {printf("\nComentario: ");}
|   gruposOpcionesDirectiva texto 
|   gruposOpcionesDirectiva NEWLINE {printf("\nNewline: %s",$1);}
|   gruposOpcionesDirectiva COMENTARIO {printf("\nComentario: ");}
|   gruposOpcionesDirectiva LPAREN RPAREN {printf("\n%s  %s",$1,$3);}
|   gruposOpcionesDirectiva LBRACKET RBRACKET {printf("\n%s  %s",$1,$3);}
|   gruposOpcionesDirectiva LBRACE RBRACE {printf("\n%s  %s",$1,$3);}
;

texto:
        IDENTIFICADOR {printf("\nIdentificador: %s",$1);}
|       PUNCTUATOR {printf("\nPunctuator: %s",$1);}
|       CONSTNUMERICA {printf("\nConstNumerica: %s",$1);}
|       LITCADENA {printf("\nLitCadena: %s",$1);}
|       texto IDENTIFICADOR {printf("\nIdentificador: %s",$1);}
|       texto PUNCTUATOR {printf("\nPunctuator: %s",$1);}
|       texto CONSTNUMERICA {printf("\nConstNumerica: %s",$1);}
|       texto LITCADENA {printf("\nLitCadena: %s",$1);}
;

%%

void yyerror(char const *s) 
{
    printf ("Error en el Parser: %s\n", s);
}

//Simbolos terminales son tokens y van en mayuscula
//Simbolos no terminales en minuscula


//yyparse() returns a value of 0 if the input it parses is valid according to the given grammar rules. 
//It returns a 1 if the input is incorrect and error recovery is impossible.

int main()
{
    yyparse();         
    printf("El programa es sintacticamente correcto");
}
