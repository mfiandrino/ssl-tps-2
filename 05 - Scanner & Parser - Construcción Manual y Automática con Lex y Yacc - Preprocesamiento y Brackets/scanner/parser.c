#include "scanner.h"
#include <stdio.h>

Token token;

int (*fun_ptr)(Token token)= nuevoToken;


static int nuevoToken(Token token){

    switch (token.type){

        case Numeral:
        
            TokenNumeral();

    }

}

char* stringTypeToken(TokenType tokTyp)
{
    switch (tokTyp)
    {
    case Comentario:
        return "(Comentario)";

    case Numeral:
        return "(Numeral)";

    case Define:
        return "(Define)";
    
    case Undefine:
        return "(Undefine)";

    case Ifdef:
        return "(Ifdef)";

    case Endif:
        return "(Endif)";

    case Include:
        return "(Include)";

    case Path:
        return "(Path)";

    case Identificador:
        return "(Identificador)";

    case TextoReemplazo:
        return "(TextoReemplazo)";

    case LParen:
        return "(LParen)";

    case RParen:
        return "(RParen)";

    case LBrack:
        return "(LBrack)";

    case RBrack:
        return "(RBrack)";
    
    case LBrace:
        return "(LBrace)";

    case RBrace:
        return "(RBrace)";

    case Punctuator:
        return "(Punctuator)";

    case LexError:
        return "(LexError)";

    case LitCadena:
        return "(LitCadena)";

    case NewLine:
        return "(NewLine)";

    case ConstNumerica:
        return "(ConstNumerica)";

    case FDT:
        return "(FDT)";

    default: // No deberia pasar
        return "Error, no deberia haber llegado aca";
    }
}

void Match (Token tokenEsperado){

    Token t;
    //GetNextToken(&t);

    if (strcmp(t.val, tokenEsperado.val) == 0){
        token.type = t.type;
        token.val = t.val;
    }else{
        ErrorSintactico();
    }

}

void TokenNumeral (void){

    GetNextToken(&token);

    switch(token.type){

       case Define:

       case Undefine:

       case Ifdef:

       case Endif:

       case Include:

       default:
            ErrorSintactico();
            break;
    }

}



void TokenDefine (void){

    GetNextToken(&token);

     switch (token.type){

         case Identificador:

        default:
            ErrorSintactico();
            break;
         
     } 

}

void TokenIdentificador (void){

    GetNextToken(&token);

     switch (token.type){

         case TextoReemplazo:

            Token t;
            t.type = NewLine;
            Match(t);

        default:
            ErrorSintactico();
            break;
         
     } 

}



//Consultar: Podemos asumir que un undef siempre termina con un newLine?
//
void TokenUndefine (void){

    GetNextToken(&token);

     switch (token.type){

         case Identificador:

        default:
            ErrorSintactico();
            break;
         
     } 

}


void ErrorSintactico(){
    printf("Ocurrió un Error Sintáctico");
}


int main ()
{
    

    while(GetNextToken(&token) && token.type != LexError)
    {

        switch (token.type){
            case Numeral:
                TokenNumeral();
            
            default:



        }


        printf("\n%s\t%s",stringTypeToken(token.type),token.val);
    }
    printf("\n%s\t\t%s",stringTypeToken(token.type),token.val);

    
    printf("\n");
}




