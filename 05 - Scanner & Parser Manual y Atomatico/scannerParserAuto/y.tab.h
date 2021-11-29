/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FDT = 0,
    LPAREN = 258,
    RPAREN = 259,
    LBRACKET = 260,
    RBRACKET = 261,
    LBRACE = 262,
    RBRACE = 263,
    NEWLINE = 264,
    COMENTARIO = 265,
    NUMERAL = 266,
    DEFINE = 267,
    IDENTIFICADOR = 268,
    TEXTOREEMPLAZO = 269,
    UNDEFINE = 270,
    INCLUDE = 271,
    LITCADENA = 272,
    IFDEF = 273,
    ELSE = 274,
    ENDIF = 275,
    PUNCTUATOR = 276,
    CONSTNUMERICA = 277
  };
#endif
/* Tokens.  */
#define FDT 0
#define LPAREN 258
#define RPAREN 259
#define LBRACKET 260
#define RBRACKET 261
#define LBRACE 262
#define RBRACE 263
#define NEWLINE 264
#define COMENTARIO 265
#define NUMERAL 266
#define DEFINE 267
#define IDENTIFICADOR 268
#define TEXTOREEMPLAZO 269
#define UNDEFINE 270
#define INCLUDE 271
#define LITCADENA 272
#define IFDEF 273
#define ELSE 274
#define ENDIF 275
#define PUNCTUATOR 276
#define CONSTNUMERICA 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "parser.y"

    char strVal[100];

#line 107 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
