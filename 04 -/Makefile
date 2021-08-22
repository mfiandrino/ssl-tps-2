# Makefile
# Makefile para compilar el TP4
# Grupo Nro 3 del curso K2051 Lunes TN
# 20210819
all : Main
BIN 	= Main
OBJ		= Main.o funciones.o stack.o
CC		= gcc
CFLAGS	= -std=c11
RM = rm -f

# Creo el ejecutable del Main
$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

#Creo el codigo objeto de Main
Main.o: main.c funciones.h stack.h
	$(CC) $(CFLAGS) -c main.c -o Main.o 

#Creo el codigo objeto de las funciones de funciones.c
funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c -o funciones.o

#Creo el codigo objeto de las funciones de stack.c
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c -o stack.o

#Creo el codigo objeto del reemplazo de comentarios
comentarios.o: comentarios.c
	$(CC) $(CFLAGS) -c comentarios.c -o comentarios.o 

clean:
	$(RM) *.o *.exe Main Test



