#include "scanner.h"
#include <stdio.h>
int main ()
{
    Token token;
    for(;;)
    {
        sleep(5);
        if(GetNextToken(&token))
            printf("Se leyo correctamente");
        else
            printf("No se leyo correctamente");
    }
    
}




