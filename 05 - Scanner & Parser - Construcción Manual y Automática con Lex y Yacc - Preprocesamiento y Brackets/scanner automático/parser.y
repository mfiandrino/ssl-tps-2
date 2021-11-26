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
 {TEXTOREEMPLAZO}			{printf("TEXTOREEMPLAZO (%s)", yytext);
 {NUMERO}					{printf("NUMERO (%s)", yytext);
 {NUMERAL}					{printf("NUMERAL (%s)", yytext);
 {DEFINE}					{printf("DEFINE (%s)", yytext);
 {PUNTO_Y_COMA}				{printf("PUNTO_Y_COMA (%s)", yytext);
 {INICIO_COMENTARIO}		{printf("INICIO_COMENTARIO (%s)", yytext);
 {FIN_COMENTARIO}			{printf("FIN_COMENTARIO (%s)", yytext);
 {LETRA}					{printf("LETRA (%s)", yytext);
 {GUIONES}					{printf("GUIONES (%s)", yytext);
 {IDENTIFICADOR}			{printf("IDENTIFICADOR (%s)", yytext);