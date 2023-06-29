
all: libvector.a

libvector.a: ./vector.o
	ar crs libvector.a ./vector.o


vector.o: ./vector.c
	gcc -Wall -Wextra -Werror -pedantic -std=c99 ./vector.c -o ./vector.o -c

clean:
	$(RM) *.o libvector.a
