CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -pedantic
LDFLAGS = -lcriterion


library :
	$(CC) $(CFLAGS) ./src/my_fnmatch.c -o ./src/my_fnmatch.o -c
	ar csr libfnmatch.a ./src/my_fnmatch.o

check : ./src/my_fnmatch.o ./tests/test.o
	$(CC) $(CFLAGS) -o ./tests/test src/my_fnmatch.o tests/test.o $(LDFLAGS)
	cd tests
	./tests/test

clean :
	$(RM) src/*.o tests/test tests/*.o libfnmatch.a

.PHONY: clean
