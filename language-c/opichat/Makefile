all: opichat_client opichat_server


opichat_client: src/basic_client/basic_client.c
	gcc -Wall -Wextra -Werror -pedantic -std=c99 $^ -o opichat_client

opichat_server: src/epoll_server/epoll-server.c src/epoll_server/connection.c src/epoll_server/utils/xalloc.c
	gcc -Wall -Wextra -fsanitize=address -g -std=c99  $^ -o opichat_server

testsuite:

clean:
	rm opichat_client opichat_server
