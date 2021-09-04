#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include"funcionesInclude.h"


int main()
{
    int retorno;
    retorno = atenderInclude();
    if (retorno == 0){
        printf ("//Reemplazo de includes correcto\n");
    }
    else if(retorno == -1){
        printf ("//No se pudo abrir el archivo del include\n");
    }
    return 0;
}


