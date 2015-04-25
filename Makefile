CC=gcc
CFLAG=-Wall -c
LFLAG=-Wall
SRC=src/main/
TEST=src/test/
BIN=bin/
OBJ=obj/

$(OBJ)%.o: $(SRC)%.c $(SRC)%.h
	@echo 'Compilation de '$^
	@$(CC) -o $@ $< $(CFLAG)

$(OBJ)%.o: $(SRC)%.c
	@echo 'Compilation de '$<
	@$(CC) -o $@ $< $(CFLAG)

$(OBJ)%.o: $(TEST)%.c $(TEST)%.h
	@echo 'Compilation de '$^ ' pour les tests'
	@$(CC) -o $@ $< $(CFLAG)

$(OBJ)%.o: $(TEST)%.c
	@echo 'Compilation de '$<' pour les tests'
	@$(CC) -o $@ $< $(CFLAG)

all:dir $(BIN)programme $(BIN)test


$(BIN)programme: $(OBJ)factorisation.o $(OBJ)producteur.o $(OBJ)consommateur.o $(OBJ)main.o
	@echo 'Compilation du programme'
	@$(CC) -o $@ $^ -lm $(LFLAG)

$(BIN)test: $(OBJ)test_factorisation.o
	@echo 'Compilation des test'
	@$(CC) -o $@ $^ -lcunit $(LFLAG)

test:$(BIN)test
	@echo 'Lancement des test'
	@valgrind --xml=yes --xml-file="valgrind.xml" ./bin/test

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

