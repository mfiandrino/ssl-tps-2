/*
Reemplazar comentarios por espacios
Grupo Nro 3 del curso K2051 Lunes TN
20210712
*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    OUT        /* fuera de un comentario*/, 
    COMMENT1  /* dentro de un comentario con // */,
    COMMENT2 /* dentro de un comentario con /* */,
}state;

int main(void){
state s = OUT;
int prevC, c;
prevC = getchar ();
while ((c=getchar())!=EOF){
    switch (s){

    case OUT:
        switch (prevC){
        case '/': //posible comentario
            switch (c){
                case '/': //comentario del tipo '//'
                    s= COMMENT1;
                    break;
                case '*': //comentario del tipo '/*'
                    s = COMMENT2;
                break;
                default: //no es comentario
                    putchar(prevC);
                    prevC=c;
                    s=OUT;
                break;
            }
        break;
        default: //no es comentario (prevC \= '/')
            putchar(prevC);
            prevC= c;
            s = OUT;
        break;
        }
    break;

    case COMMENT1: //comentario del tipo '//'
        switch (prevC){
        case '\n': //concluye el comentario
            putchar(' ');
            putchar(prevC);
            prevC = c;
            s=OUT;
        break;
        default: //continua el comentario (prevC \= '\n')
            prevC=c;
            s = COMMENT1;
        break;
        }
    break;

    default: //comentario del tipo '/*'
        switch (prevC){
        case '*': //posible cierre de comentario
            switch (c){
                case '/': //concluye el comentario
                putchar(' ');
                prevC =' ';
                s=OUT;
                break;
                default: //continua el comentario (c \= '/')
                prevC=c;
                s = COMMENT2;
                break;
            }
        break;
        default: //continua el comentario (prevC \= '*')
            prevC=c;
            s = COMMENT2;
        break;
        }
    }
}
}
