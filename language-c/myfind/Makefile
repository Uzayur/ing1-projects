CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99
OBJ= ./src/main.o ./src/parser.o ./src/action.o

all: $(OBJ)
	$(CC) $(CFLAGS) -o myfind $(OBJ)

check: myfind
	./tests/test.sh

myfind: $(OBJ)
	$(CC) $(CFLAGS) -o ./myfind $(OBJ)

clean:
	$(RM) ./src/*.o ./tests/myfind test myfind ./tests/*.o
