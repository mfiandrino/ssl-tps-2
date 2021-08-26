# Makefile
# Makefile para compilar comentarios
# Grupo Nro 3 del curso K2051 Lunes TN
# 20210712
all : atenderComentarios
BIN 	= atenderComentarios
OBJ		= atenderComentarios.o funcionesComentarios.o
CC		= gcc
CFLAGS	= -std=c11
RM = rm -f

# Creo el ejecutable del Main
$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

#Creo el codigo objeto de Main
atenderIncludes.o: atenderComentarios.c funcionesComentarios.h
	$(CC) $(CFLAGS) -c atenderComentarios.c -o funcionesComentarios.o 

#Creo el codigo objeto de las funciones de funcionesInclude.c
funcionesComentarios.o: funcionesComentarios.c funcionesComentarios.h
	$(CC) $(CFLAGS) -c funcionesComentarios.c -o funcionesComentarios.o

clean:
	$(RM) *.o *.exe Main Test

