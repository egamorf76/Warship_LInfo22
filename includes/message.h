#ifndef MESSAGE_H
#define MESSAGE_H

#include "../includes/config.h"

/// @brief message to send in socket
typedef struct {
    int serverfield[SIZE][SIZE];
    int clientfield[SIZE][SIZE];
    int isend;
    char *message;
} MESSAGE;

#endif
