%{
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>     
    #include "preprocessorSymbolTable.h"
    #include "defineSymbolTable.h"
   
    
    int yylex(void);
    void yyerror(char const *);
    //#define YYSTYPE char*
%}

%union{
    char strVal[100];
}

%token <strVal> LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE NEWLINE COMENTARIO NUMERAL DEFINE IDENTIFICADOR TEXTOREEMPLAZO UNDEFINE INCLUDE LITCADENA IFDEF ELSE ENDIF PUNCTUATOR CONSTNUMERICA FDT 0



%%

unidadDeTraduccion: grupo FDT {printf("%s",$2);}

grupo: 
    directiva
|   texto 
|   NEWLINE {printf("\nNewline: %s",$1);}
|   COMENTARIO {printf("\nComentario: ");}
|   directiva grupo
|   texto grupo
|   NEWLINE grupo {printf("\nNewline: %s",$1);}
|   COMENTARIO grupo {printf("\nComentario: ");}
|   LPAREN grupo RPAREN {printf("\n%s %s %s",$1 ,$3);}
|   LBRACKET grupo RBRACKET {printf("\n%s  %s",$1,$3);}
|   LBRACE grupo RBRACE {printf("\n%s  %s",$1,$3);}
;

directiva:  
    NUMERAL DEFINE IDENTIFICADOR CONSTNUMERICA NEWLINE {printf("\n%s  %s  %s  %s  %s",$1,$2,$3,$4,$5);}
|   NUMERAL UNDEFINE IDENTIFICADOR NEWLINE {printf("\n%s  %s  %s  %s",$1,$2,$3,$4);}
|   NUMERAL INCLUDE LITCADENA NEWLINE {printf("\n%s  %s  %s  %s",$1,$2,$3,$4);}
|   NUMERAL IFDEF IDENTIFICADOR NEWLINE gruposOpcionesDirectiva NEWLINE NUMERAL ELSE NEWLINE gruposOpcionesDirectiva NEWLINE NUMERAL ENDIF NEWLINE
;

gruposOpcionesDirectiva:
    texto 
|   NEWLINE {printf("\nNewline: %s",$1);}
|   COMENTARIO {printf("\nComentario: ");}
|   texto gruposOpcionesDirectiva
|   NEWLINE gruposOpcionesDirectiva {printf("\nNewline: %s",$1);}
|   COMENTARIO gruposOpcionesDirectiva {printf("\nComentario: ");}
|   LPAREN gruposOpcionesDirectiva RPAREN {printf("\n%s  %s",$1,$3);}
|   LBRACKET gruposOpcionesDirectiva RBRACKET {printf("\n%s  %s",$1,$3);}
|   LBRACE gruposOpcionesDirectiva RBRACE {printf("\n%s  %s",$1,$3);}
;

texto:
        IDENTIFICADOR {printf("\nIdentificador: %s",$1);}
|       PUNCTUATOR {printf("\nPunctuator: %s",$1);}
|       CONSTNUMERICA {printf("\nConstNumerica: %s",$1);}
|       LITCADENA {printf("\nLitCadena: %s",$1);}
|       IDENTIFICADOR texto {printf("\nIdentificador: %s",$1);}
|       PUNCTUATOR texto {printf("\nPunctuator: %s",$1);}
|       CONSTNUMERICA texto {printf("\nConstNumerica: %s",$1);}
|       LITCADENA texto {printf("\nLitCadena: %s",$1);}
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
