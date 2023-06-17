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
    messagesend.serverfield[SIZE][SIZE] = serverfield[SIZE][SIZE];
    messagesend.clientfield[SIZE][SIZE] = clientfield[SIZE][SIZE];
    messagesend.isend = isend;
    strncpy(messagesend.message, message, MESSAGESIZE);
    return messagesend;
}

#endif
