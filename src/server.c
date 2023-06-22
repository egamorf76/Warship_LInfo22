#include <stdio.h>
#include "../includes/message.h"
#include "../includes/boat.h"
#include "../includes/config.h"
#include "../includes/socketfds.h"
#include "../includes/socketconfig.h"
#include "gameengine.c"

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