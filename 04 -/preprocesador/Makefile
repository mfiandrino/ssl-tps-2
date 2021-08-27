# Makefile
# Makefile para compilar el preprocesador
# Grupo Nro 3 del curso K2051 Lunes TN
# 20210826

all : preprocesador
BIN 	= preprocesador
OBJ		= preprocesador.o funcionesPreprocesador.o
CC		= gcc
CFLAGS	= -std=c11
RM = rm -f

# Creo el ejecutable
$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

#Creo el codigo objeto para el ejecutable
preprocesador.o: preprocesador.c funcionesPreprocesador.h
	$(CC) $(CFLAGS) -c preprocesador.c -o preprocesador.o 

#Creo el codigo objeto de las funciones de funcionesPreprocesador.c
funcionesPreprocesador.o: funcionesPreprocesador.c funcionesPreprocesador.h
	$(CC) $(CFLAGS) -c funcionesPreprocesador.c -o funcionesPreprocesador.o
	
clean:
	$(RM) *.o *.exe preprocesador