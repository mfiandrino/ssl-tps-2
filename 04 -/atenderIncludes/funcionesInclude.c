#include <stdio.h>
#include <string.h>
#include "funcionesInclude.h"

static int esBibliotecaEstandar(int , char *);
static int esBibliotecaLocal(int , char * );

typedef enum {
    OUT /* fuera de include*/, 
    IN /* dentro de include*/
}state;

#define RUTA "C:\\MinGW\\include\\"


int esInclude (char * inc){
    int c,i;
    char palabra[] = "include";
    for (i=0; i<7; i++){
        c = getchar();
        inc[i] = c;
        }
    inc[7]='\0';
    if (strcmp(inc,palabra)==0) return 1;
    return 0;
}

void escribirIncludeFallido(char * inc){
    putchar('#');
    for (int i=0; i<7; i++){
        putchar(inc[i]);  
    }  
}

int atenderInclude (){
    int c,nc,i;
    char palabraInclude[100];
    char reemplazo[30];
    char posibleInclude[8];
    char ruta[]= RUTA;
    FILE * arch;
    state s = OUT;
    c = nc = 0;
    while ((c=getchar())!=EOF){
        switch (s)
        {
        case OUT:
            if (c == '#'){
                if(esInclude(posibleInclude)){
                    s = IN;
                }
                else {
                    escribirIncludeFallido(posibleInclude);
                    s = OUT;
                }
            }
            else{
                putchar(c);
                s = OUT;
            }
            break;
        case IN:
            if(esBibliotecaEstandar(c, palabraInclude)){
                strcat(ruta, palabraInclude);
                arch = fopen (ruta, "r");
                if (arch == NULL){
                    return -1;
                }
                else{
                    while ((nc = fgetc(arch))!= EOF)
                    {
                        putchar(nc);
                    }
                    fclose(arch);
                }
                memset(ruta, '\0', strlen(ruta));
                strcpy (ruta, RUTA);
                ruta[strlen(RUTA)+1]='\0';
            }
            else if (esBibliotecaLocal(c, palabraInclude)){ 
                arch = fopen (palabraInclude, "r");
                if (arch == NULL){
                    return -1;
                }
                else{
                    while ((nc = fgetc(arch))!= EOF)
                    {
                        putchar(nc);
                    }
                    fclose(arch);   
                }
            } 
            s = OUT;
            break;
        default:
            break;
        }
    }
    return 0;
}

static int esBibliotecaEstandar(int c, char * nombreBiblioteca){
    int i;
    if(c == '<'){
        for (i=0;((c=getchar())!='>' && (c!=EOF));i++)
        {
            nombreBiblioteca[i] = c;
        }
        nombreBiblioteca[i]='\0';
        if (c == EOF){
            return 0;
        }
        else{
            return 1;
        }
    }
    else{
        return 0;
    }
}

static int esBibliotecaLocal(int c, char * nombreBiblioteca){
    int i;
    if(c == '\"'){
        for (i=0;((c=getchar())!='\"' && (c!=EOF));i++)
        {
            nombreBiblioteca[i] = c;
        }
        nombreBiblioteca[i]='\0';
        if (c == EOF){
            return 0;
        }
        else{
            return 1;
        }
    }
    else{
        return 0;
    }
}