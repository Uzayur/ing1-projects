#define _POSIX_C_SOURCE 2008009L

#include "basic_server.h"

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int create_and_bind(struct addrinfo *addrinfo)
{
    int sockfd = 0;
    struct addrinfo *tmp;

    for (tmp = addrinfo; tmp != NULL; tmp = tmp->ai_next)
    {
        if ((sockfd =
                 socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol))
            == -1)
            continue;
        else
        {
            if (bind(sockfd, tmp->ai_addr, tmp->ai_addrlen) == -1)
                close(sockfd);
            if (listen(sockfd, 10) == -1)
                close(sockfd);

            return sockfd;
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

    return create_and_bind(info_ptr);
}

int accept_client(int socket)
{
    int r_sock = accept(socket, NULL, NULL);
    if (r_sock == -1)
    {
        close(socket);
        return 0;
    }
    return r_sock;
}

void communicate(int client_socket)
{
    char *input = calloc(9500, sizeof(char) + 1);
    if (input == NULL)
        err(1, "Malloc failed.");

    int recv_val = 0;
    if ((recv_val = recv(client_socket, input, 1024, 0)) <= 0)
        return;

    int multiple = 2;
    int count = recv_val;
    while (recv_val > 0)
    {
        input = realloc(input, sizeof(char) * multiple * 1024 + 2);
        char rec[1025];
        recv_val = recv(client_socket, rec, 1024, 0);
        rec[1024] = '\0';
        input[(multiple - 1) * 1024] = '\0';
        strcat(input, rec);
        multiple++;
        count += recv_val;
    }

    input[count] = '\0';

    if (input[count - 1] != '\n')
    {
        communicate(client_socket);
    }
    else
    {
        printf("%s", input);
        send(client_socket, input, strlen(input), MSG_NOSIGNAL);
    }
    free(input);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        printf("Usage: ./basic_server SERVER_IP SERVER_PORT\n");
    else
    {
        struct sockaddr_in client;
        int sock_server = prepare_socket(argv[1], argv[2]);

        while (1)
        {
            int clientLen = sizeof(struct sockaddr_in);
            int sock_com = accept(sock_server, (struct sockaddr *)&client,
                                  (socklen_t *)&clientLen);
            if (sock_com < 0)
                continue;
            else
            {
                printf("Client connected\n");
                communicate(sock_com);
                close(sock_com);
                printf("Client disconnected\n");
            }
        }
    }

    return 0;
}
