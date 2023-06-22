#ifndef SOCKETCONFIG_H
#define SOCKETCONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "../includes/message.h"
#include "../includes/config.h"
#include "../includes/socketfds.h"

struct SOCKETFDS createsocket() {
    // instanciation des variables
    struct SOCKETFDS socks;
    struct sockaddr_in serveraddr, clientaddr;
    int addrlen = sizeof(serveraddr);

    socks.serverfd = socket(AF_INET, SOCK_STREAM, 0);

    // creation d'une adresse locale
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    // association de l'adresse locale a la socket
    bind(socks.serverfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in));

    // attente des clients
    listen(socks.serverfd, 1);

    // attendre la connexion entrante
    socks.clientfd = accept(socks.serverfd, (struct sockaddr *)&clientaddr, (socklen_t *)&addrlen);
    if (socks.clientfd < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    return socks;
}

int connectsocket() {
    // Instanciation des variables
    struct sockaddr_in serveraddr;

    // ouverture d'une sockfdet
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // creation adresse de la machine distante
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    inet_aton("127.0.0.1", &serveraddr.sin_addr);

    // on demande un connection sur l'adresse distante
    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    return sockfd;
}

int createsendmessage(int sockfd, const int serverfield[SIZE][SIZE], const int clientfield[SIZE][SIZE], const int isend, const char *message) {
    // create and send message to server
    struct MESSAGE messagesend = createmessage(serverfield, clientfield, isend, message);
    send(sockfd, &messagesend, MAXDATASIZE, 0);
    memset(&messagesend, 0, sizeof(messagesend));
}

#endif