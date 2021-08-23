# Makefile
# Makefile para compilar histograma
# Grupo Nro 3 del curso K2051 Lunes TN
# 20210712
all : atenderIncludes
BIN 	= atenderIncludes
OBJ		= atenderIncludes.o funcionesInclude.o
CC		= gcc
CFLAGS	= -std=c11
RM = rm -f

# Creo el ejecutable del Main
$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

#Creo el codigo objeto de Main
atenderIncludes.o: atenderIncludes.c funcionesInclude.h
	$(CC) $(CFLAGS) -c atenderIncludes.c -o atenderIncludes.o 

#Creo el codigo objeto de las funciones de funcionesInclude.c
funcionesInclude.o: funcionesInclude.c funcionesInclude.h
	$(CC) $(CFLAGS) -c funcionesInclude.c -o funcionesInclude.o

clean:
	$(RM) *.o *.exe Main Test

