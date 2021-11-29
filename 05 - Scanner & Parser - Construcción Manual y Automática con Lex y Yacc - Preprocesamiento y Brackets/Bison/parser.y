%{
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>     
    #include "../preprocessorSymbolTable/preprocessorSymbolTable.h"
    #include "../defineSymbolTable/defineSymbolTable.h"
    
    void yyerror(char const *s) {printf ("Error en el Parser: %s\n", s);}
    int yylex(void);

    int deletePrep(char*);
 %}
 

 
%union {   
    char strVal[100];
    int intVal;
}



%token <strVal> NEWLINE COMENTARIO  NUMERAL DEFINE IDENTIFICADOR TEXTOREEMPLAZO UNDEFINE INCLUDE LITCADENA IFDEF ELSE ENDIF PUNCTUATOR CONSTNUMERICA FDT 0

%type <strVal> unidadDeTraduccion listaDeGrupos grupo gruposOpcionales directiva texto gruposOpcionesDirectiva textosOpcionales

%%

unidadDeTraduccion: listaDeGrupos FDT;

listaDeGrupos: grupo gruposOpcionales;

gruposOpcionales: grupo;

grupo: directiva
|    texto 
|    NEWLINE
|    COMENTARIO
|    gruposOpcionales 
;

directiva:  NUMERAL DEFINE IDENTIFICADOR CONSTNUMERICA NEWLINE {printf("\n El identificador es %s", $3);}
|    NUMERAL UNDEFINE IDENTIFICADOR NEWLINE
|    NUMERAL INCLUDE LITCADENA NEWLINE
|    NUMERAL IFDEF IDENTIFICADOR NEWLINE gruposOpcionesDirectiva NEWLINE NUMERAL ELSE NEWLINE gruposOpcionesDirectiva NEWLINE NUMERAL ENDIF NEWLINE
;

gruposOpcionesDirectiva: grupo;

texto:  IDENTIFICADOR textosOpcionales
|    PUNCTUATOR textosOpcionales
|    CONSTNUMERICA textosOpcionales
|    LITCADENA textosOpcionales
;

textosOpcionales: texto;

%%

//Simbolos terminales son tokens y van en mayuscula
//Simbolos no terminales en minuscula


//yyparse() returns a value of 0 if the input it parses is valid according to the given grammar rules. 
//It returns a 1 if the input is incorrect and error recovery is impossible.
void parser(){

    if(yyparse())   
        printf("\n Error sintactico\n");
    else        
        return;
        
            

    

}
