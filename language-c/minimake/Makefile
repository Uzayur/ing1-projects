CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -g
LDFLAGS=-lcriterion
FILES= src/handle_var.o src/handle_rule.o src/handle_command.o src/handle_stack.o src/minimake.o src/handle_pretty_print.o

minimake: $(FILES)
	$(CC) $(CFLAGS) -o minimake $^

check: ./tests/test.o
	$(CC) $(CFLAGS) -o tests/test_suite $^ $(LDFLAGS)
	./tests/test_suite

clean:
	$(RM) src/*.o minimake tests/*.o tests/test_suite

.PHONY: clean
