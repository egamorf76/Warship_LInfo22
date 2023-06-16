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

    MESSAGE messagerecv;

    // reception bateaux du client
    read(sockfd, &messagerecv, sizeof(messagerecv));
    
    printf("Client : %s\n", messagerecv.message);
    printf("Client : %d\n", messagerecv.isend);
    serverfield[SIZE][SIZE] = messagerecv.serverfield[SIZE][SIZE];

    memset(&messagerecv, 0, sizeof(messagerecv));

    // create message
    MESSAGE messagesend;
    messagesend.serverfield[SIZE][SIZE] = serverfield[SIZE][SIZE];
    messagesend.clientfield[SIZE][SIZE] = clientfield[SIZE][SIZE];
    messagesend.isend = 0;
    strncpy(messagesend.message, "Client send field", MESSAGESIZE);

    // send message
    send(sockfd, &messagesend, sizeof(messagesend), 0);
    memset(&messagesend, 0, sizeof(messagesend));

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

    close(sockfd);

    return 0;
}