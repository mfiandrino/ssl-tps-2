#include "funcionesPreprocesador.h"

typedef enum {
    BUSCAR_COMENTARIO,
    BUSCAR_DEFINE_INCLUDE, 
    COMILLAS,
    CARACTER_COMUN,  
    COMENTARIO1, 
    COMENTARIO2,
    DEFINE,
    INCLUDE, 
    UNDEF
}estado;

static int atenderComillas(int,estado*);
static void atenderNumeral();
static void atenderComentarioMultiLinea(int*,int, estado*);
static void atenderComentarioDeLinea(int*, int, estado*);
static void analizarPosibleComentario(int*,int, estado*);
static void atenderPosibleComentario(int, estado*);

int preprocesador()
{
    int c;
    estado s = CARACTER_COMUN;

    while ((c=getchar())!= EOF) 
    {
        switch (s)
        {
            case CARACTER_COMUN:
                if(c == '#')
                    atenderNumeral(c);
                else if(c == '/')
                    atenderPosibleComentario(c,&s);
                else if(c == '\"' || c == '\'')
                    if(atenderComillas(c,&s))
                        break;
                    else
                        return -2; // Error porque llega a EOF sin cerrar comillas
                else
                    putchar(c);
                break;  
        }
    }
}

esUndef(int i){
    char palabra[] = "undef";
}

esDefine(int i){
    char palabra[] = "define";
}

esInclude(int i){
    char palabra[] = "include";
}



static void atenderNumeral(int c, estado *s)
{
    *s = BUSCAR_DEFINE_INCLUDE;
    int c;
    char inc[7];
        for (int i = 0; i < 7; i++ ){
            c = getchar();
            inc[i] = c;

           esUndef(i);
           esDefine(i);
           esInclude(i);

        }

    putchar(c);
    return;
}


static void atenderComentarioMultiLinea(int *prevC,int c, estado *s)
{
    switch (*prevC) 
    {
        case '*': //posible cierre de comentario
            switch (c)
            {
                case '/': //concluye el comentario
                    putchar(' ');
                    *prevC =' ';                    
                    *s = CARACTER_COMUN;
                    break;
                default: //continua el comentario (c \= '/')
                    *prevC=c;
                    *s = COMENTARIO2;
            }
        break;
        default: //continua el comentario (prevC \= '*')
            *prevC=c;
            *s = COMENTARIO2;
    }
}


static void atenderComentarioDeLinea(int *prevC, int c, estado *s)
{
    switch (*prevC)
    {
        case '\n': //concluye el comentario
            putchar(' ');
            putchar(*prevC);
            *prevC = c;
            //*s=OUT;
            *s = CARACTER_COMUN;
            break;
        default: //continua el comentario (prevC \= '\n')
            *prevC=c;
            *s = COMENTARIO1;
    }
}

static void analizarPosibleComentario(int *prevC,int c, estado *s)
{
    switch (c)
    {
        case '/': //comentario del tipo '//'
            *s= COMENTARIO1;
            break;
        case '*': //comentario del tipo '/*'
            *s = COMENTARIO2;
            break;

        default: //no es comentario
            putchar(*prevC);
            *prevC=c;
            *s = CARACTER_COMUN;            
            break;
    }
}
                
    

static void atenderPosibleComentario(int prevC, estado *s)
{
    *s = BUSCAR_COMENTARIO;
    
    int c;
    while ((c=getchar())!=EOF && (*s != CARACTER_COMUN))
    {
        switch (*s)
        {
            case BUSCAR_COMENTARIO:
                analizarPosibleComentario(&prevC,c,&s);
                break;

            case COMENTARIO1: //comentario del tipo '//'
                atenderComentarioDeLinea(&prevC,c,&s);
                break;

            default: //comentario del tipo '/*'
                atenderComentarioMultiLinea(&prevC,c,&s);
        }
    }
}

static int atenderComillas(int caracter,estado *estado)
{
    putchar(caracter);
    int caracterAux;
    *estado = COMILLAS;
    caracterAux = caracter;
    while ((caracter=getchar())!=EOF)
    {
        putchar(caracter);
        if(caracter == '\\') //En caso de que el codigo haga referencia a la comilla simple o doble \' \"
        {
            getchar(); // Ignoro el siguiente caracter
            putchar(caracter);
        }

        if(caracter == caracterAux) //Si cierran las comillas
        {
            *estado = CARACTER_COMUN;
            return 1;
        }
            
    }
    if (caracter == EOF) //Si no encontre la comilla que cierra y llegue a EOF
        return 0;
}

