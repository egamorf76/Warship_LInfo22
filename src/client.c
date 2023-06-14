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
#include "gameengine.c"
#include "../includes/message.h"

#define PORT 3490
#define MAXDATASIZE 1024

/// @brief Connect and start game
/// @return 0 for exit and 1 for finish
int startconnect()
{
    // Instanciation des variables
    MESSAGE messagerecv;
    struct sockaddr_in sock_host;
    int sock, val_read;
    char buf[MAXDATASIZE];

    // Les variables de jeux
    BOAT clientboats[number_boats];
    int clientfield[SIZE][SIZE];
    int serverfield[SIZE][SIZE];

    buildarrays(clientfield, EMPTY);
    placeboats(clientfield, clientboats);

    // ouverture d'une socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // on cre l'adresse de la machine distante
    memset(&sock_host, '\0', sizeof(sock_host));
    sock_host.sin_family = AF_INET;
    sock_host.sin_port = htons(PORT);
    inet_aton("127.0.0.1", &sock_host.sin_addr);

    // on demande un connection sur l'adresse distante
    connect(sock, (struct sockaddr *)&sock_host, sizeof(sock_host));

    // reception bateaux du client
    if ((read(sock, buf, MAXDATASIZE)) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    //clientfield[SIZE][SIZE] = messagerecv.clientfield;
    printf("Server : %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // envoie au serveur
    //MESSAGE messagesend = {serverfield, clientfield, 0, "Client send field"};

    if (send(sock,/*(void *) &messagesend*/ "test client",/*sizeof(messagesend)*/ strlen("test client"), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // reception bateaux du client
        if ((val_read=recv(sock, (struct recvrtu *)&messagerecv, sizeof(messagerecv), 0)) == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        }

        serverfield[SIZE][SIZE] = messagerecv.serverfield;
        clientfield[SIZE][SIZE] = messagerecv.clientfield;
        printf(messagerecv.message);

        if (messagerecv.isend == 1) {
            return 1;
        }

        // fin ?
        if (isend(clientboats, clientboats) == 1) {
            // envoie au serveur
            MESSAGE messagesend = {serverfield, clientfield, 1, "Server win"};

            if (send(sock,(void *) &messagesend ,sizeof(messagesend), 0) == -1) {
                perror("send");
                exit(EXIT_FAILURE);
            };
            return 1;
        }

        // client joue un tour
        if (playround(serverfield, clientfield) != 1) {
            return 0;
        }

        // envoie au serveur
        MESSAGE messagesend = {serverfield, clientfield, 0, "Client played"};

        if (send(sock,(void *) &messagesend ,sizeof(messagesend), 0) == -1) {
            perror("send");
            exit(EXIT_FAILURE);
        }
    }
}