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

unidadDeTraduccion: grupo FDT

grupo: 
    directiva
|   texto 
|   NEWLINE {printf("\n");}
|   COMENTARIO {printf(" ");}
|   directiva grupo
|   texto grupo
|   NEWLINE grupo {printf("\n);}
|   COMENTARIO grupo {printf(" ");}
|   LPAREN grupo RPAREN {printf("\n%s %s",$1,$3);}
|   LBRACKET grupo RBRACKET {printf("\n%s  %s",$1,$3);}
|   LBRACE grupo RBRACE {printf("\n%s  %s",$1,$3);}
;

directiva:  
    NUMERAL DEFINE IDENTIFICADOR CONSTNUMERICA NEWLINE  { set($3, $4); setPrep($3, idDefine);}
|   NUMERAL UNDEFINE IDENTIFICADOR NEWLINE              { delete($3); deletePrep($3);}
|   NUMERAL INCLUDE LITCADENA NEWLINE                   { traerArchivoInclude($3);}
|   NUMERAL IFDEF IDENTIFICADOR NEWLINE gruposOpcionesDirectiva NEWLINE NUMERAL ELSE NEWLINE gruposOpcionesDirectiva NEWLINE NUMERAL ENDIF NEWLINE
;

gruposOpcionesDirectiva:
    texto
|   NEWLINE {printf("\n");}
|   COMENTARIO {printf(" ");}
|   texto gruposOpcionesDirectiva
|   NEWLINE gruposOpcionesDirectiva {printf("\n");}
|   COMENTARIO gruposOpcionesDirectiva {printf(" ");}
|   LPAREN gruposOpcionesDirectiva RPAREN {printf("\n%s  %s",$1,$3);}
|   LBRACKET gruposOpcionesDirectiva RBRACKET {printf("\n%s  %s",$1,$3);}
|   LBRACE gruposOpcionesDirectiva RBRACE {printf("\n%s %s",$1,$3);}
;

texto:
        IDENTIFICADOR {imprimirIdentificador($1);}
|       PUNCTUATOR {printf($1);}
|       CONSTNUMERICA {printf($1);}
|       LITCADENA {printf("\"%s\"", $1);}
|       IDENTIFICADOR texto {imprimirIdentificador($1);}
|       PUNCTUATOR texto {printf($1);}
|       CONSTNUMERICA texto {printf($1);}
|       LITCADENA texto {printf("\"%s\"", $1);}
;

%%

void yyerror(char const *s) 
{
    printf ("Error en el Parser: %s\n", s);
}

static void traerArchivoInclude(char *path)
{
    int nc;
    FILE *arch = fopen (path, "r");
    if (arch == NULL)
    {
        printf("No existe el archivo");
        exit(-1);
    }
    else
    {
        while ((nc = fgetc(arch))!= EOF)
            putchar(nc);

        fclose(arch);
        printf("\n");
    }
}

void imprimirIdentificador(){
    IdType tipoToken = getPrep(token.val);    
      
    if ( tipoToken != idDefine){           
        printf("%s ",token.val);
    } else {            
        textoReemplazo = get(token.val);
        printf("%s ",textoReemplazo);
    }
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
