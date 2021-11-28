%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 
    #include "../preprocessorSymbolTable/preprocessorSymbolTable.h"
    #include "../defineSymbolTable/defineSymbolTable.h"

    int yylex(void);
    void yyerror(char const *s){printf ("Error en el Parser: %s\n", s);} ;
    
 %}
 
 %option noyywrap 
 
%union {    
    char strVal[100];
}

%token <strVal> NEWLINE COMENTARIO FDT NUMERAL DEFINE IDENTIFICADOR TEXTOREEMPLAZO UNDEFINE INCLUDE LITCADENA IFDEF ELSE ENDIF PUNCTUATOR CONSTNUMERICA 

%type <strVal> unidadDeTraducción listaDeGrupos grupo gruposOpcionales directiva texto gruposOpcionesDirectiva textosOpcionales

%%

unidadDeTraducción: listaDeGrupos FDT;

listaDeGrupos: grupo gruposOpcionales;

grupo: 
  directiva
|    texto 
|    NEWLINE
|    COMENTARIO
|    ( <GruposOpcionales> )
|    [ <GruposOpcionales> ]
|    { <GruposOpcionales> }
;

directiva:
|    NUMERAL DEFINE IDENTIFICADOR CONSTNUMERICA NEWLINE  {set($3,$4);}
|    NUMERAL UNDEFINE IDENTIFICADOR NEWLINE
|    NUMERAL INCLUDE LITCADENA NEWLINE
|    NUMERAL IFDEF IDENTIFICADOR NEWLINE <GruposOpcionales> NEWLINE NUMERAL ELSE NEWLINE <GruposOpcionales> NEWLINE NUMERAL ENDIF NEWLINE
;

Texto: 
    Identificador <TextosOpcionales>  printf 
    Punctuator <TextosOpcionales>
    ConstNumerica <TextosOpcionales>
    LitCadena <TextosOpcionales>




%%

//Simbolos terminales son tokens y van en mayuscula
//Simbolos no terminales en minuscula


//yyparse() returns a value of 0 if the input it parses is valid according to the given grammar rules. 
//It returns a 1 if the input is incorrect and error recovery is impossible.
void parser(){

    if(yyparse())   
        printf("\n Error \n");
    else        
        return;
        
            

    

}






%%
 {Textoreemplazo}   {printf("(Textoreemplazo) (%s)", yytext);}
 {ConstNumerica}    {printf("(ConstNumerica) (%s)", yytext);}
 {Numeral}  {printf("(Numeral) (%s)", yytext);}
 {Define}   {printf("(Define) (%s)", yytext);}
 {Undefine} {printf("(Undefine) (%s)", yytext);}
 {Ifdef}    {printf("(Ifdef) (%s)", yytext);}
 {Endif}    {printf("(Endif) (%s)", yytext);}
 {Include}  {printf("(Include) (%s)", yytext);}
 {Punctuator}   {printf("(Punctuator) (%s)", yytext);} 
 {Comentario}   {printf("(Comentario) (%s)", yytext);}
 {Identificador}    {printf("(Identificador) (%s)", yytext);}
 {LParen}   {printf("(LParen) (%s)", yytext);}
 {RParen}   {printf("(RParen) (%s)", yytext);}
 {LBrack}   {printf("(LBrack) (%s)", yytext);}
 {RBrack}   {printf("(RBrack) (%s)", yytext);}
 {LBrace}   {printf("(LBrace) (%s)", yytext);}
 {RBrace}   {printf("(RBrace) (%s)", yytext);}
 {LexError}  {printf("(LexError) (%s)", yytext);}    
 {LitCadena} {printf("(LitCadena) (%s)", yytext);}
 {NewLine} {printf("(NewLine) (%s)", yytext);}
 {FDT}   {printf("(FDT) (%s)", yytext);}
.   {return "Error, no deberia haber llegado;}
%%