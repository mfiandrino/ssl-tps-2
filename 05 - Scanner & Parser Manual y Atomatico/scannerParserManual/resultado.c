int printf(const char * restrict, ...);
int main (void )
{
 
char s []="hola",*p ="chau";

int a [10  ];
printf ("%d\t%d\n",sizeof s ,sizeof p );
p =s ;
printf ("%p\t%p\t%p\t%p\n",s ,&s ,s ,&s );
printf ("%p",&a ); 
printf ("\n");
}

 