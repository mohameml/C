CC=gcc
CCOPT= -O2 -Wall
OBJ=../bin
SRC=.

all: $(OBJ)/perfMesureCommand

$(OBJ)/perfMesure.o: $(SRC)/perfMesure.c $(SRC)/perfMesure.h
	$(CC) $(CCOPT) -c $(SRC)/perfMesure.c -o $(OBJ)/perfMesure.o

$(OBJ)/perfMesureCommand: $(SRC)/perfMesureCommand.c $(SRC)/perfMesure.h $(OBJ)/perfMesure.o
	$(CC) $(CCOPT) -o $(OBJ)/perfMesureCommand $(SRC)/perfMesureCommand.c $(OBJ)/perfMesure.o

clean:
	rm -f $(OBJ)/perfMesure.o $(OBJ)/perfMesureCommand

