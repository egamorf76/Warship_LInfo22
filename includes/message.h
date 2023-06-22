#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include "../includes/config.h"
#include "../includes/array.h"

/// @brief message to send in socket
struct MESSAGE {
    int serverfield[SIZE][SIZE];
    int clientfield[SIZE][SIZE];
    int isend;
    char message[MESSAGESIZE];
};

struct MESSAGE createmessage(const int serverfield[SIZE][SIZE], const int clientfield[SIZE][SIZE], const int isend, const char *message) {
    // create and send message to server
    struct MESSAGE messagesend;
    copyarray(messagesend.serverfield, serverfield);
    copyarray(messagesend.clientfield, clientfield);
    messagesend.isend = isend;
    strncpy(messagesend.message, message, MESSAGESIZE);
    return messagesend;
}

#endif
