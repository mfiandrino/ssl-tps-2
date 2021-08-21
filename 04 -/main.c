#include "funciones.h"

int main()
{
    int resultado = balanceoDeBrackets();
    if(resultado == 1)
        printf("\nLos brackets estan balanceados\n");
    else if (resultado == 0)
        printf("\nLos brackets NO estan balanceados\n");
    else
        printf("\nLas comillas NO estan balanceadas\n");
        
    getchar();
    getchar();
    getchar();

}