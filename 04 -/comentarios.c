/*
Reemplazar comentarios por espacios
Grupo Nro 3 del curso K2051 Lunes TN
20210712
*/
#include <string.h>
#include <stdio.h>

int main(void){
    int prevC;
    int c;
    prevC = getchar ();
    while ((c=getchar())!=EOF)
    {
        if ((prevC == '/') && (c == '*')) goto IN1;
        //if ((prevC == '/') && (c == '/')) goto IN2;
        else goto OUT;

        OUT:
        putchar(prevC);
        prevC = c;

        IN1:
        if ((prevC == '/') && (c == '*'))
        {
            prevC = getchar();
            c = getchar();
        }
        //printf("previo if \n");
        while ( (prevC != '*') && (c != '/'))
        {
            prevC = c;
            c = getchar();
        }
        if ( (prevC == '*') && (c == '/'))
        {
            putchar(' ');
            prevC = c;
        }
        /*
        IN2:
        //if (c == '\n'){
        //    putchar(' ');
        //    c = getchar();
            //prevC = c;
        //    goto OUT;}
        //else prevC = c;
        while (c != '\n')
        {
            printf("adentro1");
            prevC = c;
            printf("adentro2");
            c = getchar();
            printf("adentro3");
        }
        printf("salio");
        putchar(' ');
        prevC = c;
        //goto OUT;
        */

    }
    
    //putchar(prevC); 

}
