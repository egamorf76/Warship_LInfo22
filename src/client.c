#include <stdio.h>
#include "../includes/message.h"
#include "../includes/boat.h"
#include "../includes/config.h"
#include "../includes/socketconfig.h"
#include "gameengine.c"

int main(int argc, char const *argv[])
{
    // Instanciation des variables
    char buffer[MAXDATASIZE] = {0};
    BOAT clientboats[number_boats];
    int clientfield[SIZE][SIZE];
    int serverfield[SIZE][SIZE];
    struct MESSAGE messagerecv;

    buildarrays(clientfield, EMPTY);
    placeboats(clientfield, clientboats);

    int sockfd = connectsocket();

    // recevied and read message from server
    recv(sockfd, &buffer, sizeof(buffer), 0);
    memcpy(&messagerecv, buffer, sizeof messagerecv);

    printf("Client : %s\n", messagerecv.message);
    copyarray(serverfield, messagerecv.serverfield);

    memset(&buffer, 0, sizeof(buffer));
    memset(&messagerecv, 0, sizeof(messagerecv));

    createsendmessage(sockfd, serverfield, clientfield, 0, "Client send field");

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
        memset(&messagerecv, 0, sizeof(messagerecv));

        // fin ?
        if (isend(clientfield, clientboats) == 1) {
            createsendmessage(sockfd, serverfield, clientfield, 1, "Server win");
            printf("Server win");
            return 1;
        }

        // client joue un tour
        if (playround(clientfield, serverfield) != 1) {
            return 0;
        }

        createsendmessage(sockfd, serverfield, clientfield, 0, "Client played");
    }

    close(sockfd);

    return 0;
}