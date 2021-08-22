# Makefile
# Makefile para compilar la funcionalidad de balanceo de brackets
# Grupo Nro 3 del curso K2051 Lunes TN
# 20210822
all : balanceoDeBrackets
BIN 	= balanceoDeBrackets
OBJ		= balanceoDeBrackets.o funcionesBalanceo.o stack.o
CC		= gcc
CFLAGS	= -std=c11
RM = rm -f

# Creo el ejecutable
$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

#Creo el codigo objeto para el ejecutable
balanceoDeBrackets.o: balanceoDeBrackets.c funcionesBalanceo.h ../stack.h
	$(CC) $(CFLAGS) -c balanceoDeBrackets.c -o balanceoDeBrackets.o 

#Creo el codigo objeto de las funciones de funcionesBalanceo.c
funcionesBalanceo.o: funcionesBalanceo.c funcionesBalanceo.h
	$(CC) $(CFLAGS) -c funcionesBalanceo.c -o funcionesBalanceo.o

#Creo el codigo objeto de las funciones de stack.c
stack.o: ../stack.c ../stack.h
	$(CC) $(CFLAGS) -c ../stack.c -o stack.o

#Creo el codigo objeto del reemplazo de comentarios
comentarios.o: comentarios.c
	$(CC) $(CFLAGS) -c comentarios.c -o comentarios.o 

clean:
	$(RM) *.o *.exe balanceoDeBrackets
