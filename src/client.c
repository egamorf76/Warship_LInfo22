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
    char currentmessage[MESSAGESIZE];

    buildarrays(clientfield, EMPTY);
    placeboats(clientfield, clientboats);

    int sockfd = connectsocket();

    // recevied and read message from server
    recv(sockfd, &buffer, sizeof(buffer), 0);
    memcpy(&messagerecv, buffer, sizeof messagerecv);

    copyarray(serverfield, messagerecv.serverfield);

    memset(&buffer, 0, sizeof(buffer));
    
    strncpy(currentmessage, "\nClient : fields sent\n", sizeof currentmessage);
    createsendmessage(sockfd, serverfield, clientfield, 0, currentmessage);

    while (1) {
        // recevied and read message from server
        read(sockfd, &buffer, sizeof(buffer));
        memcpy(&messagerecv, buffer, sizeof messagerecv);

        copyarray(serverfield, messagerecv.serverfield);
        copyarray(clientfield, messagerecv.clientfield);

        // quit if client win
        if (messagerecv.isend == 1) {
            return 1;
        }

        memset(&buffer, 0, sizeof(buffer));

        // fin ?
        strncpy(currentmessage, "\nClient : played\n", sizeof currentmessage);

        if (isend(clientfield, clientboats, currentmessage) == 1) {
            strncpy(currentmessage, "\nClient : Server win\n", sizeof currentmessage);
            createsendmessage(sockfd, serverfield, clientfield, 1, currentmessage);
            printf("%s", currentmessage);
            return 1;
        }

        // client joue un tour
        if (playround(clientfield, serverfield, currentmessage, messagerecv.message) != 1) {
            return 0;
        }

        createsendmessage(sockfd, serverfield, clientfield, 0, currentmessage);
    }

    close(sockfd);

    return 0;
}