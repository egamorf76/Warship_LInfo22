#include "../includes/config.h"

#ifndef ARRAY_H
#define ARRAY_H

/// @brief Fill 2D array with value
/// @param field Initialized 2D array
/// @param value Value filled
void buildarrays(int field[SIZE][SIZE], int const value) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            field[i][j] = value;
        }
    }
}

/// @brief Copy 2D array
/// @param dest Destinatary 2D array
/// @param src Source 2D array
int copyarray(int dest[SIZE][SIZE], const int src[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
    return 1;
}

#endif
