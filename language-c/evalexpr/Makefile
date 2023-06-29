CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra
LDFLAGS = -lcriterion

all: evalexpr

evalexpr: src/evalexpr.o
	$(CC) $(CFLAGS) -o src/evalexpr src/evalexpr.o

check: ./src/function.o ./tests/test.o
	$(CC) $(CFLAGS) -o tests/test src/function.o tests/test.o $(LDFLAGS)
	./tests/test

clean:
	$(RM) src/*.o tests/test.o tests/test src/evalexpr
