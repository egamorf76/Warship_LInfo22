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
    char currentmessage[MESSAGESIZE];

    buildarrays(serverfield, EMPTY);
    placeboats(serverfield, serverboats);

    struct SOCKETFDS socks = createsocket();

    // create and send message to server
    strncpy(currentmessage, "\nServer : fields sent\n", sizeof currentmessage);
    createsendmessage(socks.clientfd, serverfield, clientfield, 0, currentmessage);

    // recevied and read message from server
    recv(socks.clientfd, &buffer, sizeof(buffer), 0);
    memcpy(&messagerecv, buffer, sizeof messagerecv);

    copyarray(clientfield, messagerecv.clientfield);

    memset(&buffer, 0, sizeof(buffer));

    while (1) {
        // serveur joue un tour
        if (playround(serverfield, clientfield, currentmessage, messagerecv.message) != 1) {
            return 0;
        }

        // create and send message to server
        strncpy(currentmessage, "\nServer : played\n", sizeof currentmessage);
        createsendmessage(socks.clientfd, serverfield, clientfield, 0, currentmessage);

        // recevied and read message from server
        read(socks.clientfd, &buffer, sizeof(buffer));
        memcpy(&messagerecv, buffer, sizeof messagerecv);

        copyarray(serverfield, messagerecv.serverfield);
        copyarray(clientfield, messagerecv.clientfield);

        if (messagerecv.isend == 1) {
            return 1;
        }

        memset(&buffer, 0, sizeof(buffer));

        // fin ?
        if (isend(serverfield, serverboats) == 1) {
            strncpy(currentmessage, "\nServer : Client win\n", sizeof currentmessage);
            createsendmessage(socks.clientfd, serverfield, clientfield, 1, currentmessage);
            printf("%s", currentmessage);
            return 1;
        }
    }

    close(socks.clientfd);
    close(socks.serverfd);

    return 0;
}