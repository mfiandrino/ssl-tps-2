#include <stdbool.h>

typedef enum {
    Comentario,
    Numeral,
    Define,
    Undefine,
    Ifdef,
    Else,
    Endif,
    Include,
    Identificador,
    LParen='(', 
    RParen=')', 
    LBrack='[', 
    RBrack=']', 
    LBrace='{', 
    RBrace='}', 
    Punctuator, 
    LexError,
    LitCadena,
    NewLine,
    ConstNumerica,
    FDT
} TokenType;

typedef struct{
    TokenType type;
    char* val;
} Token;

// Retorna si pudo leer, almacena en t el token leido.
int GetNextToken(Token *t);
