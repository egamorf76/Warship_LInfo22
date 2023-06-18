#ifndef MESSAGE_H
#define MESSAGE_H

#include "../includes/config.h"

/// @brief message to send in socket
struct MESSAGE {
    int serverfield[SIZE][SIZE];
    int clientfield[SIZE][SIZE];
    int isend;
    char message[MESSAGESIZE];
};

struct MESSAGE createmessage(int serverfield[SIZE][SIZE], int clientfield[SIZE][SIZE], int isend, char *message) {
    // create and send message to server
    struct MESSAGE messagesend;
    copyarray(messagesend.serverfield, serverfield);
    copyarray(messagesend.clientfield, clientfield);
    messagesend.isend = isend;
    strncpy(messagesend.message, message, MESSAGESIZE);
    return messagesend;
}

#endif
