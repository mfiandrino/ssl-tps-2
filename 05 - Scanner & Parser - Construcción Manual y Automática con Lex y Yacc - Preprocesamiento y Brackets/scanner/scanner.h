#include <stdbool.h>

typedef enum {
    Comentario,
    Numeral,
    Define,
    Undefine,
    Ifdef,
    Endif,
    Include,
    Path,
    Identificador,
    TextoReemplazo,
    LParen='(',
    RParen=')',
    LBrack='[',
    RBrack=']',
    LBrace='{',
    RBrace='}',
    Punctuator,
    LexError,
    LitCadena,
    LitCaracter
} TokenType;

typedef struct{
    TokenType type;
    char* val;
} Token;

// Retorna si pudo leer, almacena en t el token leido.
bool GetNextToken(Token *t);