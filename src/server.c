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
    // instanciation des variables
    struct sockaddr_in serveraddr, clientaddr;
    int sockfd, newsockfd;
    int addrlen = sizeof(serveraddr);
    char buffer[MAXDATASIZE] = {0};

    // variables de jeux
    BOAT serverboats[number_boats];
    int serverfield[SIZE][SIZE];
    int clientfield[SIZE][SIZE];
    struct MESSAGE messagerecv;
    struct MESSAGE messagesend;

    buildarrays(serverfield, EMPTY);
    placeboats(serverfield, serverboats);

    // ouverture d'une socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // creation d'une adresse locale
    memset(&serveraddr, '\0', sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    // association de l'adresse locale a la socket
    bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in));

    // attente des clients
    listen(sockfd, 1);

    // attendre la connexion entrante
    if ((newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // create and send message to server
    messagesend = createmessage(serverfield, clientfield, 0, "Server send field");
    send(newsockfd, &messagesend, MAXDATASIZE, 0);
    memset(&messagesend, 0, sizeof(messagesend));

    // recevied and read message from server
    read(newsockfd, &messagerecv, sizeof(messagerecv));

    printf("Server : %s\n", messagerecv.message);
    clientfield[SIZE][SIZE] = messagerecv.clientfield[SIZE][SIZE];

    memset(&messagerecv, 0, sizeof(messagerecv));

    //while (1) {
        sleep(3);

        // serveur joue un tour
        if (playroundnoretry(serverfield, clientfield) != 1) {
            return 0;
        }

        // create and send message to server
        messagesend = createmessage(serverfield, clientfield, 0, "Server send field");
        send(newsockfd, &messagesend, MAXDATASIZE, 0);
        memset(&messagesend, 0, sizeof(messagesend));

        // recevied and read message from server
        read(newsockfd, &messagerecv, sizeof(messagerecv));

        clientfield[SIZE][SIZE] = messagerecv.clientfield[SIZE][SIZE];
        serverfield[SIZE][SIZE] = messagerecv.serverfield[SIZE][SIZE];
        printf("Server : %s\n", messagerecv.message);

        if (messagerecv.isend == 1) {
            return 1;
        }

        memset(&messagerecv, 0, sizeof(messagerecv));

        // fin ?
        if (isend(serverfield, serverboats) == 1) {
            // create and send message to server
            messagesend = createmessage(serverfield, clientfield, 0, "Client win");
            send(newsockfd, &messagesend, MAXDATASIZE, 0);
            memset(&messagesend, 0, sizeof(messagesend));

            printf("Client win");
            return 1;
        }
    //}

    close(sockfd);
    close(newsockfd);

    return 0;
}