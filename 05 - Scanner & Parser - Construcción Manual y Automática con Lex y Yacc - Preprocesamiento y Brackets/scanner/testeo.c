#include "printf.h"
#define MAX 10
int main(void)
{
    /*  Declara un arreglo y un puntero
        para demostrar algunas
        diferencias y similitudes */
    char s[]="hola", *p="chau";
#ifdef MAX
    int a[MAX];
#else
    int a;
#endif
    printf("%d\t%d\n", sizeof s, sizeof p);
#undef MAX
    p=s;
    printf("%p\t%p\t%p\t%p\n", s, &s, s, &s);
#ifdef MAX
    // muestra el contenido de los primeros MAX ints
    for(unsigned i=0;i<MAX;++i)
    printf("%d\t", a[i]);
#else
    printf("%p", &a); // muestra la dirección de a
#endif
    printf("\n");
}

/*
int printf(const char * restrict, ...);

int main(void){
    char s[]="hola", *p="chau";
    int a[10];
    printf("%zu\t%zu\n", sizeof s, sizeof p);
    p=s;
    printf("%p\t%p\t%p\t%p\n", s, &s, s, &s);
    printf("%p", &a);
    printf("\n");
}
*/