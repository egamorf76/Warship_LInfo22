#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
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
#include "gameengine.c"

int main(int argc, char const *argv[])
{
    // Instanciation des variables
    struct sockaddr_in serveraddr;
    fd_set serverset;
    int sockfd;
    char buffer[MAXDATASIZE] = {0};

    // Les variables de jeux
    BOAT clientboats[number_boats];
    int clientfield[SIZE][SIZE];
    int serverfield[SIZE][SIZE];
    struct MESSAGE messagerecv;
    struct MESSAGE messagesend;

    buildarrays(clientfield, EMPTY);
    placeboats(clientfield, clientboats);

    // ouverture d'une sockfdet
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // creation adresse de la machine distante
    memset(&serveraddr, '\0', sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    inet_aton("127.0.0.1", &serveraddr.sin_addr);

    // on demande un connection sur l'adresse distante
    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    // recevied and read message from server
    recv(sockfd, &buffer, sizeof(buffer), 0);
    memcpy(&messagerecv, buffer, sizeof messagerecv);

    printf("Client : %s\n", messagerecv.message);
    copyarray(serverfield, messagerecv.serverfield);

    memset(&buffer, 0, sizeof(buffer));
    memset(&messagerecv, 0, sizeof(messagerecv));

    // create and send message to server
    messagesend = createmessage(serverfield, clientfield, 0, "Client send field");
    send(sockfd, &messagesend, MAXDATASIZE, 0);
    memset(&messagesend, 0, sizeof(messagesend));

    while (1) {
        // recevied and read message from server
        read(sockfd, &buffer, sizeof(buffer));
        memcpy(&messagerecv, buffer, sizeof messagerecv);

        copyarray(serverfield, messagerecv.serverfield);
        copyarray(clientfield, messagerecv.clientfield);
        printf("Client : %s\n", messagerecv.message);

        // quit if client win
        if (messagerecv.isend == 1) {
            return 1;
        }

        memset(&buffer, 0, sizeof(buffer));
        memset(&messagesend, 0, sizeof(messagesend));

        // fin ?
        if (isend(clientfield, clientboats) == 1) {
            // create and send message to client
            messagesend = createmessage(serverfield, clientfield, 0, "Server win");
            send(sockfd, &messagesend, MAXDATASIZE, 0);
            memset(&messagesend, 0, sizeof(messagesend));

            printf("Server win");
            return 1;
        }

        // client joue un tour
        if (playround(clientfield, serverfield) != 1) {
            return 0;
        }

        // create and send message to server
        messagesend = createmessage(serverfield, clientfield, 0, "Client played");
        send(sockfd, &messagesend, MAXDATASIZE, 0);
        memset(&messagesend, 0, sizeof(messagesend));
    }

    close(sockfd);

    return 0;
}