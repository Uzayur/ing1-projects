#define _POSIX_C_SOURCE 2008009L

#include "basic_client.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void communicate(int server_socket)
{
    char *input = NULL;

    fprintf(stderr, "Enter your message:");

    size_t index = 0;

    index = getline(&input, &index, stdin);
    send(server_socket, input, index, 0);

    if (index == 1)
    {
        char output[DEFAULT_BUFFER_SIZE] = { 0 };
        recv(server_socket, output, DEFAULT_BUFFER_SIZE, 0);
        printf("Server answered with: %s", output);
    }
    else
    {
        int multiple = 1 + index / DEFAULT_BUFFER_SIZE;

        char output[DEFAULT_BUFFER_SIZE * multiple];

        recv(server_socket, output, DEFAULT_BUFFER_SIZE * multiple, 0);
        printf("Server answered with: %s", output);
    }
    free(input);
}

int create_and_connect(struct addrinfo *addrinfo)
{
    int sockfd = 0;
    struct addrinfo *tmp;

    for (tmp = addrinfo; tmp != NULL; tmp = tmp->ai_next)
    {
        if ((sockfd = socket(addrinfo->ai_family, addrinfo->ai_socktype,
                             addrinfo->ai_protocol))
            == -1)
            continue;

        if (connect(sockfd, addrinfo->ai_addr, addrinfo->ai_addrlen) == -1)
        {
            close(sockfd);
            continue;
        }
        else
        {
            communicate(sockfd);
            close(sockfd);
            return 0;
        }
    }
    return 1;
}

int prepare_socket(const char *ip, const char *port)
{
    struct addrinfo info;
    struct addrinfo *info_ptr;
    memset(&info, 0, sizeof(info));
    info.ai_family = AF_UNSPEC;
    info.ai_socktype = SOCK_STREAM;
    info.ai_flags = AI_PASSIVE;

    int addrinfo = getaddrinfo(ip, port, &info, &info_ptr);

    if (addrinfo)
        return 1;

    return create_and_connect(info_ptr);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./basic_client SERVER_IP SERVER_PORT\n");
        exit(1);
    }
    return prepare_socket(argv[1], argv[2]);
}
