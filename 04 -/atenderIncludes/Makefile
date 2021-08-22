# Makefile
# Makefile para compilar histograma
# Grupo Nro 3 del curso K2051 Lunes TN
# 20210712
all : Main
BIN 	= Main
OBJ		= Main.o funcionesInclude.o
CC		= gcc
CFLAGS	= -std=c11
RM = rm -f

# Creo el ejecutable del Main
$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

#Creo el codigo objeto de Main
Main.o: main.c funcionesInclude.h
	$(CC) $(CFLAGS) -c main.c -o Main.o 

#Creo el codigo objeto de las funciones de funcionesInclude.c
funcionesInclude.o: funcionesInclude.c funcionesInclude.h
	$(CC) $(CFLAGS) -c funcionesInclude.c -o funcionesInclude.o

clean:
	$(RM) *.o *.exe Main Test

