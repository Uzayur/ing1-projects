library: ./fifo.o
	ar crs libfifo.a ./fifo.o

fifo.o: ./fifo.c
	gcc -Wall -Wextra -Werror -pedantic -std=c99 *.c -o ./fifo.o -c

clean:
	$(RM) *.o libfifo.a

