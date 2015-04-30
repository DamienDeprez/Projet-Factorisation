CC=gcc
CFLAG=-Wall -c -g
LFLAG=-Wall -g
SRC=src/
TEST=src/
BIN=bin/
OBJ=obj/

$(OBJ)%.o: $(SRC)%.c $(SRC)%.h
	@echo 'Compilation de '$^
	@$(CC) -o $@ $< $(CFLAG)

$(OBJ)%.o: $(SRC)%.c
	@echo 'Compilation de '$<
	@$(CC) -o $@ $< $(CFLAG)

all:dir $(BIN)programme $(BIN)test


$(BIN)programme: $(OBJ)factorisation.o $(OBJ)producteur.o $(OBJ)consommateur.o $(OBJ)main.o $(OBJ)buffer.o
	@echo 'Compilation du programme'
	@$(CC) -o $@ $^ -lm -lpthread -lcurl $(LFLAG)

$(BIN)test: $(OBJ)test_factorisation.o $(OBJ)factorisation.o $(OBJ)buffer.o
	@echo 'Compilation des test'
	@$(CC) -o $@ $^ -lcunit -lm -lpthread -lcurl $(LFLAG)

test:$(BIN)test
	@echo 'Lancement des test'
	@valgrind --xml=yes --xml-file="valgrind.xml" --leak-check=full --track-origins=yes --show-leak-kinds=all  ./bin/test

.PHONY: clean purge dir

dir:
	@mkdir $(OBJ) $(BIN) $(SRC) -p

clean:
	@echo 'Nettoyage des fichiers temporaires'
	@find ./ -name '*.o' -print0 | xargs -0 rm -f
	@find ./ -name '*~' -print0 | xargs -0 rm -f

purge: clean
	@echo 'Suppression des fichiers exécutable'
	@find $(BIN) -type f -print0 | xargs -0 rm -f

