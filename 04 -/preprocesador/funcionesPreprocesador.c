#include "funcionesPreprocesador.h"

typedef enum {
    BUSCAR_COMENTARIO,
    BUSCAR_DEFINE_INCLUDE, 
    COMILLAS,
    CARACTER_COMUN
}state;

typedef enum {
    OUT,
    COMMENT1, 
    COMMENT2
}estadoComentarios;

static int atenderComillas(int,state*);
static void atenderNumeral();
static void atenderComentarioMultiLinea(int*,int, estadoComentarios*, state*);
static void atenderComentarioDeLinea(int*, int, estadoComentarios*, state*);
static void analizarPosibleComentario(int*,int, estadoComentarios*, state*);
static void atenderPosibleComentario(int, state*);

int preprocesador()
{
    int c;
    state s = CARACTER_COMUN;

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

static void atenderNumeral(int c)
{
    putchar(c);
    return;
}

static void atenderComentarioMultiLinea(int *prevC,int c, estadoComentarios *s, state *estado)
{
    switch (*prevC)
    {
        case '*': //posible cierre de comentario
            switch (c)
            {
                case '/': //concluye el comentario
                    putchar(' ');
                    *prevC =' ';
                    //*s=OUT;
                    *estado = CARACTER_COMUN;
                    break;
                default: //continua el comentario (c \= '/')
                    *prevC=c;
                    *s = COMMENT2;
            }
        break;
        default: //continua el comentario (prevC \= '*')
            *prevC=c;
            *s = COMMENT2;
    }
}


static void atenderComentarioDeLinea(int *prevC, int c, estadoComentarios *s, state *estado)
{
    switch (*prevC)
    {
        case '\n': //concluye el comentario
            putchar(' ');
            putchar(*prevC);
            *prevC = c;
            //*s=OUT;
            *estado = CARACTER_COMUN;
            break;
        default: //continua el comentario (prevC \= '\n')
            *prevC=c;
            *s = COMMENT1;
    }
}

static void analizarPosibleComentario(int *prevC,int c, estadoComentarios *s, state *estado)
{
    switch (c)
    {
        case '/': //comentario del tipo '//'
            *s= COMMENT1;
            break;
        case '*': //comentario del tipo '/*'
            *s = COMMENT2;
            break;

        default: //no es comentario
            putchar(*prevC);
            *prevC=c;
            *estado = CARACTER_COMUN;
            //*s=OUT;
            break;
    }
}
                
    

static void atenderPosibleComentario(int prevC, state *estado)
{
    *estado = BUSCAR_COMENTARIO;

    estadoComentarios s = OUT;
    int c;
    while ((c=getchar())!=EOF && *estado == BUSCAR_COMENTARIO)
    {
        switch (s)
        {
            case OUT:
                analizarPosibleComentario(&prevC,c,&s,estado);
                break;

            case COMMENT1: //comentario del tipo '//'
                atenderComentarioDeLinea(&prevC,c,&s,estado);
                break;

            default: //comentario del tipo '/*'
                atenderComentarioMultiLinea(&prevC,c,&s,estado);
        }
    }
}

static int atenderComillas(int caracter,state *estado)
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

