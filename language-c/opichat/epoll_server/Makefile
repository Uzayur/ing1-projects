BIN= epoll-server.c connection.c utils/xalloc.c

epoll_server:
	gcc -Wall -Wextra -fsanitize=address -g -std=c99  $(BIN) -o epoll_server

clean:
	$(RM) epoll_server *.swp *.o

