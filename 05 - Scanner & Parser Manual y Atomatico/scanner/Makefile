all : parser
BIN 	= parser
OBJ		= parser.o scanner.o prepSymbolTable.o defSymbolTable.o
CC		= gcc
CFLAGS	= -std=c11
RM = rm -f

# Creo el ejecutable
$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

#Creo el codigo objeto para el ejecutable
parser.o: parser2.c scanner.h ../defineSymbolTable/defineSymbolTable.h ../preprocessorSymbolTable/preprocessorSymbolTable.h
	$(CC) $(CFLAGS) -c parser2.c -o parser.o 

#Creo el codigo objeto del modulo scanner
scanner.o: scanner.c scanner.h ../preprocessorSymbolTable/preprocessorSymbolTable.h
	$(CC) $(CFLAGS) -c scanner.c -o scanner.o

#Creo el codigo objeto de las funciones de defineSymbolTable.c
defSymbolTable.o: ../defineSymbolTable/defineSymbolTable.c ../defineSymbolTable/defineSymbolTable.h
	$(CC) $(CFLAGS) -c ../defineSymbolTable/defineSymbolTable.c -o defSymbolTable.o

#Creo el codigo objeto de las funciones de symbolTable.c
prepSymbolTable.o: ../preprocessorSymbolTable/preprocessorSymbolTable.c ../preprocessorSymbolTable/preprocessorSymbolTable.h
	$(CC) $(CFLAGS) -c ../preprocessorSymbolTable/preprocessorSymbolTable.c -o prepSymbolTable.o

clean:
	$(RM) *.o *.exe parser
