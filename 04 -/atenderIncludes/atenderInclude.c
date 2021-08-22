#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    OUT /* fuera de una palabra*/, 
    IN /* dentro de una palabra*/
}state;



int main()
{
    int c,nc,i;
    char palabraInclude[100];
    char reemplazo[30];
    char inc[9];
    char palabra[] = "include ";
    state s = OUT;
    c = nc = 0;
    while ((c=getchar())!=EOF){
        //putchar(c);
        switch (s)
        {
        case OUT:
            if (c == '#'){
                for (i=0; i<8; i++){
                    c = getchar();
                    //putchar(c);
                    inc[i] = c;
                }
                inc[8]='\0';
                nc = strcmp(inc,palabra);
                //printf("nc: %d\ninc: %s\npalabra: %s\n",nc,inc, palabra);
                if(strcmp(inc,palabra)==0){
                    s = IN;

                }
                else {
                    s = OUT;
                    break;
                }
            }
            break;
        case IN:
            if((c = getchar())=='<'){
                for (i=0;((c=getchar())!='>' && (c!=EOF));i++)
                {
                    //putchar(c);
                    palabraInclude[i] = c;
                }
                //putchar(c);
                palabraInclude[++i]='\0';
                printf("Libreria: %s\n",palabraInclude);
                s = OUT;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}




