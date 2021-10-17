#include <stdbool.h>

typedef enum {
    Comentario, //Listo
    Numeral, //Listo
    Define, //Listo
    Undefine, //Listo
    Ifdef,
    Endif, 
    Include, //Listo
    Path, //Uso LitCadena
    Identificador, //Listo
    TextoReemplazo, //Listo
    LParen='(', //Listo
    RParen=')', //Listo
    LBrack='[', //Listo
    RBrack=']', //Listo
    LBrace='{', //Listo
    RBrace='}', //Listo
    Punctuator, //Listo
    LexError, //Listo
    LitCadena, //Listo
    NewLine, //Listo
    FDT //Listo
} TokenType;

typedef struct{
    TokenType type;
    char* val;
} Token;

// Retorna si pudo leer, almacena en t el token leido.
bool GetNextToken(Token *t);