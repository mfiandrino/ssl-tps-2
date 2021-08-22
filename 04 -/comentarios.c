/*
Reemplazar comentarios por espacios
Grupo Nro 3 del curso K2051 Lunes TN
20210712
*/


#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    OUT /* fuera de una palabra*/, 
    IN /* dentro de una palabra*/,
    IN2,
}state;

int main(void){
state s = OUT;
int prevC, c;
prevC = getchar ();
while ((c=getchar())!=EOF){
    switch (s){
    case OUT:
        switch (prevC){
        case '/':
            switch (c){
                case '/':
                s= IN;
                break;
                case '*':
                s = IN2;
                break;
                default:
                putchar(prevC);
                prevC=c;
                s=OUT;
                break;
            }
        break;
        default: //(prevC /= '/')
        putchar(prevC);
        prevC= c;
        s = OUT;
        break;
        }
    break;
    case IN:
        switch (prevC){
        case '\n':
        putchar(' ');
        putchar(prevC);
        prevC = c;
        s=OUT;
        break;
        default: //(prevC /= '\n')
        prevC=c;
        s = IN;
        break;
        }
    break;
    default:
        switch (prevC){
        case '*':
            switch (c){
                case '/':
                putchar(' ');
                prevC =' ';
                s=OUT;
                break;
                default:
                prevC=c;
                s = IN2;
                break;
            }
        break;
        default:
        prevC=c;
        s = IN2;
        break;
        }
    }
}
}
