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
    // Instanciation des variables
    struct sockaddr_in serveraddr;
    int sockfd;
    char buffer[MAXDATASIZE] = {0};
    char message[MAXDATASIZE];

    // Les variables de jeux
    BOAT clientboats[number_boats];
    int clientfield[SIZE][SIZE];
    int serverfield[SIZE][SIZE];

    buildarrays(clientfield, EMPTY);
    placeboats(clientfield, clientboats);

    // ouverture d'une sockfdet
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // on cre l'adresse de la machine distante
    memset(&serveraddr, '\0', sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    inet_aton("127.0.0.1", &serveraddr.sin_addr);

    // on demande un connection sur l'adresse distante
    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    // reception bateaux du client
    
    read(sockfd, buffer, MAXDATASIZE);
    printf("Client : %s\n", buffer);
    memset(buffer, 0, sizeof(buffer));

    // clientfield[SIZE][SIZE] = messagerecv.clientfield;

    // envoie au serveur
    //MESSAGE messagesend = {serverfield, clientfield, 0, "Client send field"};

    // if (send(sock,/*(void *) &messagesend*/ "test client",/*sizeof(messagesend)*/ strlen("test client"), 0) == -1) {
    //     perror("send");
    //     exit(EXIT_FAILURE);
    // }

    strncpy(message, "Test client", MAXDATASIZE);
    send(sockfd, message, strlen(message), 0);

    memset(message, 0, sizeof(message));


    // while (1) {
    //     // reception bateaux du client
    //     if ((val_read=recv(sockfd, (struct recvrtu *)&messagerecv, sizeof(messagerecv), 0)) == -1) {
    //         perror("recv");
    //         exit(EXIT_FAILURE);
    //     }

    //     serverfield[SIZE][SIZE] = messagerecv.serverfield;
    //     clientfield[SIZE][SIZE] = messagerecv.clientfield;
    //     printf(messagerecv.message);

    //     if (messagerecv.isend == 1) {
    //         return 1;
    //     }

    //     // fin ?
    //     if (isend(clientboats, clientboats) == 1) {
    //         // envoie au serveur
    //         MESSAGE messagesend = {serverfield, clientfield, 1, "Server win"};

    //         if (send(sockfd,(void *) &messagesend ,sizeof(messagesend), 0) == -1) {
    //             perror("send");
    //             exit(EXIT_FAILURE);
    //         };
    //         return 1;
    //     }

    //     // client joue un tour
    //     if (playround(serverfield, clientfield) != 1) {
    //         return 0;
    //     }

    //     // envoie au serveur
    //     MESSAGE messagesend = {serverfield, clientfield, 0, "Client played"};

    //     if (send(sockfd,(void *) &messagesend ,sizeof(messagesend), 0) == -1) {
    //         perror("send");
    //         exit(EXIT_FAILURE);
    //     }
    // }

    return 0;
}