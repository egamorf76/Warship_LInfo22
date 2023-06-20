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
#include "../includes/boat.h"
#include "../includes/config.h"
#include "../includes/socketfds.h"
#include "gameengine.c"

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

int createsendmessage(int sockfd, const int serverfield[SIZE][SIZE], const int clientfield[SIZE][SIZE], const int isend, const char *message) {
    // create and send message to server
    struct MESSAGE messagesend = createmessage(serverfield, clientfield, isend, message);
    send(sockfd, &messagesend, MAXDATASIZE, 0);
    memset(&messagesend, 0, sizeof(messagesend));
}

int main(int argc, char const *argv[])
{
    // instanciation des variables
    char buffer[MAXDATASIZE] = {0};
    BOAT serverboats[number_boats];
    int serverfield[SIZE][SIZE];
    int clientfield[SIZE][SIZE];
    struct MESSAGE messagerecv;

    buildarrays(serverfield, EMPTY);
    placeboats(serverfield, serverboats);

    struct SOCKETFDS socks = createsocket();

    printf("new socket: %d", socks.clientfd);
    printf("new socket: %d", socks.serverfd);

    // create and send message to server
    createsendmessage(socks.clientfd, serverfield, clientfield, 1, "Server send field");

    // recevied and read message from server
    recv(socks.clientfd, &buffer, sizeof(buffer), 0);
    memcpy(&messagerecv, buffer, sizeof messagerecv);

    printf("Server : %s\n", messagerecv.message);
    copyarray(clientfield, messagerecv.clientfield);

    memset(&buffer, 0, sizeof(buffer));
    memset(&messagerecv, 0, sizeof(messagerecv));

    while (1) {
        // serveur joue un tour
        if (playround(serverfield, clientfield) != 1) {
            return 0;
        }

        // create and send message to server
        createsendmessage(socks.clientfd, serverfield, clientfield, 0, "Server played");

        // recevied and read message from server
        read(socks.clientfd, &buffer, sizeof(buffer));
        memcpy(&messagerecv, buffer, sizeof messagerecv);

        copyarray(serverfield, messagerecv.serverfield);
        copyarray(clientfield, messagerecv.clientfield);
        printf("Server : %s\n", messagerecv.message);

        if (messagerecv.isend == 1) {
            return 1;
        }

        memset(&buffer, 0, sizeof(buffer));
        memset(&messagerecv, 0, sizeof(messagerecv));

        // fin ?
        if (isend(serverfield, serverboats) == 1) {
            createsendmessage(socks.clientfd, serverfield, clientfield, 0, "Client win");
            printf("Client win");
            return 1;
        }
    }

    close(socks.clientfd);
    close(socks.serverfd);

    return 0;
}