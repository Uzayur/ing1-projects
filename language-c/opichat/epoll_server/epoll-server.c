#define _POSIX_C_SOURCE 2008009L
#include "epoll-server.h"

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "connection.h"
#include "utils/xalloc.h"

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
            {
                err(1, "Bind has failed...\n");
                close(sockfd);
            }
            if (listen(sockfd, 10) == -1)
            {
                err(1, "Listen has failed...\n");
                close(sockfd);
            }

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

struct connection_t *accept_client(int epoll_instance, int server_socket,
                                   struct connection_t *connections)
{
    int client_fd = accept(server_socket, NULL, NULL);
    if (find_client(connections, client_fd) != NULL)
    {
        return NULL;
    }

    if (client_fd == -1)
    {
        close(client_fd);
        return NULL;
    }

    connections = add_client(connections, client_fd);

    struct epoll_event *event = xmalloc(sizeof(struct epoll_event));
    event->events = EPOLLIN;
    event->data.fd = client_fd;

    if (epoll_ctl(epoll_instance, EPOLL_CTL_ADD, client_fd, event) == -1)
    {
        err(1, "Add client to list of interest has failed...");
    }

    return connections;
}

void send_all(struct connection_t *clients, char *message, int len)
{
    for (struct connection_t *curr = clients; curr; curr = curr->next)
    {
        send(curr->client_socket, message, len, MSG_NOSIGNAL);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        printf("Usage: ./basic_server SERVER_IP SERVER_PORT\n");
    else
    {
        int server = prepare_socket(argv[1], argv[2]);
        int epoll_fd = epoll_create1(0);
        if (epoll_fd == -1)
            err(1, "Can't create epoll.");

        struct epoll_event event;
        event.events = EPOLLIN;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server, &event) == -1)
        {
            err(1, "Instantiate epoll has failed...");
        }

        struct connection_t *connections = xmalloc(sizeof(struct connection_t));
        connections = NULL;
        while (1)
        {
            struct epoll_event events[MAX_EVENTS];
            int events_count = 0;
            struct connection_t *client = NULL;

            events_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

            for (int event_id = 0; event_id < events_count; event_id++)
            {
                int client_fd = events[event_id].data.fd;
                char message[1024];
                if (connections != NULL)
                {
                    client = find_client(connections, client_fd);
                }

                if (client == NULL)
                {
                    struct connection_t *accept =
                        accept_client(epoll_fd, server, connections);
                    if (accept != NULL)
                        connections = accept;
                }
                else
                {
                    memset(message, 0, 1024);
                    int read_len = read(client_fd, message, 1024);
                    send_all(connections, message, read_len);
                }
            }
        }
        free(connections);
    }
    return 0;
}
