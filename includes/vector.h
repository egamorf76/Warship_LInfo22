#ifndef VECTOR_H
#define VECTOR_H

#include <string.h>
#include <stdio.h>
#include "config.h"

/// @brief 2D vector of 2 integers : X and Y
typedef struct {
    int X;
    int Y;
} VECTOR;

 void tostring(char *message, VECTOR const pos) {
    char str[4];
    sprintf(str, "%c%d", ALPHABET[pos.X], pos.Y + 1);
    strncpy(message, str, 4);
}

#endif

