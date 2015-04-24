CC=gcc
CFLAG=-Wall -c
LFLAG=-Wall
SRC=src/
BIN=bin/
OBJ=obj/

$(OBJ)%.o: $(SRC)%.c $(SRC)%.h
	@echo 'Compilation de '$^
	@$(CC) -o $@ $< $(CFLAG)

$(OBJ)%.o: $(SRC)%.c
	@echo 'Compilation de '$<
	@$(CC) -o $@ $< $(CFLAG)

all:$(BIN)programme


$(BIN)programme: $(OBJ)factorisation.o $(OBJ)producteur.o $(OBJ)consommateur.o $(OBJ)main.o
	@echo 'Compilation du programme'
	@$(CC) -o $@ $^ $(LFLAG)

.PHONY: clean purge

clean:
	@echo 'Nettoyage des fichiers temporaires'
	@find -name "*.o" -print0 | xargs -0 rm
	@find -name "*~" -print0 | xargs -0 rm

purge: clean
	@echo 'Suppression des fichiers exécutable'
	@find $(BIN) -type f 

