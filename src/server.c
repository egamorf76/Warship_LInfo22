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

/// @brief start game as server
/// @return 0 for exit game and 1 for finished game
int startserver()
{
    // instanciation des variables
    MESSAGE messagerecv;
    struct sockaddr_in my_adr;
    struct sockaddr_in serveur_adr;
    socklen_t sz_sock_serveur;
    int sock, sock_distante, val_read;
    int addrlen = sizeof(my_adr);
    char buf[MAXDATASIZE];

    // Les variables de jeux
    BOAT serverboats[number_boats];
    int serverfield[SIZE][SIZE];
    int clientfield[SIZE][SIZE];

    buildarrays(serverfield, EMPTY);
    placeboats(serverfield, serverboats);

    printf("test");

    // ouverture d'une socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // cration d'une adresse locale
    memset(&my_adr, '\0', sizeof(my_adr));
    my_adr.sin_family = AF_INET;
    my_adr.sin_port = htons(PORT);
    my_adr.sin_addr.s_addr = INADDR_ANY;

    // association de l'adresse locale a la socket
    bind(sock, (struct sockaddr *)&my_adr, sizeof(struct sockaddr_in));

    // attente des clients
    listen(sock, 1);
    printf("Attend la connection d'un autre joueur");
    
    // Attendre la connexion entrante
    if ((sock_distante = accept(sock, (struct sockaddr *)&serveur_adr, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // envoie bateaux au client
    //MESSAGE messagesend = {serverfield, clientfield, 1, "Server send field"};

    if (send(sock,/*(void *) &messagesend*/ "test Serveur",/*sizeof(messagesend)*/ strlen("test Serveur"), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    // reception bateaux du client
    if ((read(sock_distante, buf, MAXDATASIZE)) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    //clientfield[SIZE][SIZE] = messagerecv.clientfield;
    printf("Client : %s\n", buf);
    memset(buf, 0, sizeof(buf));

    while (1) {
        // serveur joue un tour
        if (playround(serverfield, clientfield) != 1) {
            return 0;
        }

        // envoie au client
        MESSAGE messagesend = {serverfield, clientfield, 0, "Serveur played"};

        if (send(sock_distante,(void *) &messagesend ,sizeof(messagesend), 0) == -1) {
            perror("send");
            exit(EXIT_FAILURE);
        }
        
        // reception du client
        if ((val_read=recv(sock_distante, (struct recvrtu *)&messagerecv, sizeof(messagerecv), 0)) == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        }

        clientfield[SIZE][SIZE] = messagerecv.clientfield;
        serverfield[SIZE][SIZE] = messagerecv.serverfield;
        printf(messagerecv.message);

        if (messagerecv.isend == 1) {
            return 1;
        }

        // fin ?
        if (isend(serverfield, serverboats) == 1) {
            // envoie au client
            MESSAGE messagesend = {serverfield, clientfield, 0, "Client win"};

            if (send(sock_distante,(void *) &messagesend ,sizeof(messagesend), 0) == -1) {
                perror("send");
                exit(EXIT_FAILURE);
            }
            return 1;
        }
    }
}