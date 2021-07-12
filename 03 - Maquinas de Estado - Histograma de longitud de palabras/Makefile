# Makefile
# Makefile para compilar histograma
# Grupo Nro 3 del curso K2051 Lunes TN
# 20210707
all : Main Test
BIN 	= Main
BIN2  =  Test
OBJ		= Main.o Graficador.o histograma1.o histograma2.o histograma3.o histogramaX.o funcionesHistograma.o
OBJ2  =  Test.o Graficador.o histograma1.o histograma2.o histograma3.o histogramaX.o funcionesHistograma.o
CC		= gcc
CFLAGS	= -std=c11
RM = rm -f

# Creo el ejecutable del Main
$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

# Creo el ejecutable del Test
$(BIN2): $(OBJ2) 
	$(CC) $(CFLAGS) $(OBJ2) -o $(BIN2)

#Creo el codigo objeto de Main
Main.o: main.c Graficador.h histograma.h
	$(CC) $(CFLAGS) -c main.c -o Main.o 

#Creo el codigo objeto de Test
Test.o: Test.c Graficador.h histograma.h
	$(CC) $(CFLAGS) -c Test.c -o Test.o 

#Creo el codigo objeto de las funciones de Graficador.c
Graficador.o: Graficador.c Graficador.h
	$(CC) $(CFLAGS) -c Graficador.c -o Graficador.o

#Creo el codigo objeto de las funciones del histograma-1-enum-switch.c
histograma1.o: histograma-1-enum-switch.c histograma.h
	$(CC) $(CFLAGS) -c histograma-1-enum-switch.c -o histograma1.o

#Creo el codigo objeto de las funciones del histograma-2-goto.c
histograma2.o: histograma-2-goto.c histograma.h
	$(CC) $(CFLAGS) -c histograma-2-goto.c -o histograma2.o

#Creo el codigo objeto de las funciones del histograma-3-rec.c
histograma3.o: histograma-3-rec.c histograma.h
	$(CC) $(CFLAGS) -c histograma-3-rec.c -o histograma3.o

#Creo el codigo objeto de las funciones del histograma-x.c
histogramaX.o: histograma-x.c histograma.h
	$(CC) $(CFLAGS) -c histograma-x.c -o histogramaX.o

#Creo el codigo objeto de las funciones generales del histograma
funcionesHistograma.o: funcionesHistograma.c histograma.h
	$(CC) $(CFLAGS) -c funcionesHistograma.c -o funcionesHistograma.o

clean:
	$(RM) *.o *.exe



