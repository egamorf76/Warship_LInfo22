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
#include "../includes/boat.h"
#include "../includes/config.h"
#include "gameengine.c"

int main(int argc, char const *argv[])
{
    // instanciation des variables
    struct sockaddr_in serveraddr, clientaddr;
    int sockfd, newsockfd;
    int addrlen = sizeof(serveraddr);
    char buffer[MAXDATASIZE] = {0};
    char message[MAXDATASIZE];

    // Les variables de jeux
    BOAT serverboats[number_boats];
    int serverfield[SIZE][SIZE];
    int clientfield[SIZE][SIZE];

    buildarrays(serverfield, EMPTY);
    placeboats(serverfield, serverboats);

    // ouverture d'une socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // cration d'une adresse locale
    memset(&serveraddr, '\0', sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    // association de l'adresse locale a la socket
    bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in));

    // attente des clients
    listen(sockfd, 1);

    // Attendre la connexion entrante
    if ((newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // envoie bateaux au client
    // MESSAGE messagesend = {serverfield, clientfield, 1, "Server send field"};
    // if (send(sockfd, void *) &messagesend, sizeof(messagesend), 0) == -1) {
    //     perror("send");
    //     exit(EXIT_FAILURE);
    // }

    strncpy(message, "Test server", MAXDATASIZE);
    send(newsockfd, message, strlen(message), 0);
    memset(message, 0, sizeof(message));


    // reception bateaux du client

    read(newsockfd, buffer, MAXDATASIZE);
    printf("Server : %s\n", buffer);
    memset(buffer, 0, sizeof(buffer));

    // clientfield[SIZE][SIZE] = messagerecv.clientfield;

    // while (1) {
    //     // serveur joue un tour
    //     if (playround(serverfield, clientfield) != 1) {
    //         return 0;
    //     }

    //     // envoie au client
    //     MESSAGE messagesend = {serverfield, clientfield, 0, "Serveur played"};

    //     if (send(newsockfd,(void *) &messagesend ,sizeof(messagesend), 0) == -1) {
    //         perror("send");
    //         exit(EXIT_FAILURE);
    //     }

    //     // reception du client
    //     if ((val_read=recv(newsockfd, (struct recvrtu *)&messagerecv, sizeof(messagerecv), 0)) == -1) {
    //         perror("recv");
    //         exit(EXIT_FAILURE);
    //     }

    //     clientfield[SIZE][SIZE] = messagerecv.clientfield;
    //     serverfield[SIZE][SIZE] = messagerecv.serverfield;
    //     printf(messagerecv.message);

    //     if (messagerecv.isend == 1) {
    //         return 1;
    //     }

    //     // fin ?
    //     if (isend(serverfield, serverboats) == 1) {
    //         // envoie au client
    //         MESSAGE messagesend = {serverfield, clientfield, 0, "Client win"};

    //         if (send(newsockfd,(void *) &messagesend ,sizeof(messagesend), 0) == -1) {
    //             perror("send");
    //             exit(EXIT_FAILURE);
    //         }
    //         return 1;
    //     }
    // }

    return 0;
}