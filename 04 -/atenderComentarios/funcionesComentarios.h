#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int atenderComentarios(void);

typedef enum {
    OUT        /* fuera de un comentario*/, 
    COMMENT1  /* dentro de un comentario con // */,
    COMMENT2 /* dentro de un comentario con /* */,
}state;