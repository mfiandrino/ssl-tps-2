all : main
BIN 	= main
OBJ		= main.o scanner.o
CC		= gcc
CFLAGS	= -std=c11
RM = rm -f

# Creo el ejecutable
$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

#Creo el codigo objeto para el ejecutable
main.o: main.c scanner.h
	$(CC) $(CFLAGS) -c main.c -o main.o 

#Creo el codigo objeto del modulo scanner
scanner.o: scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c -o scanner.o

clean:
	$(RM) *.o *.exe main
