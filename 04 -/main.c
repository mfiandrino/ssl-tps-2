#include "funciones.h"

int main()
{
    if(balanceoDeBrackets() == 1)
        printf("\nLos brackets estan balanceados\n");
    else if (balanceoDeBrackets() == 0)
        printf("\nLos brackets NO estan balanceados\n");
    else
        printf("\nLas comillas NO estan balanceadas\n");
        
    getchar();
    getchar();
    getchar();

}