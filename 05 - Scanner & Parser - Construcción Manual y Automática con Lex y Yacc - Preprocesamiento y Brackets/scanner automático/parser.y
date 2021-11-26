%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 
    int yylex(void);
    void yyerror(char *s);
    FILE *yyin;
 %}
 
 %option noyywrap 
 %option yylineno

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