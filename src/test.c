#include <stdio.h>
#include "../includes/boat.h"
#include "../includes/config.h"
#include "../includes/socketfds.h"
#include "gameengine.c"

int main(int argc, char const *argv[])
{
    int field[SIZE][SIZE];
    BOAT serverboats[number_boats];
    char fieldstr[256];

    buildarrays(field, EMPTY);
    placeboats(field, serverboats);

    strcat(fieldstr, "message\n");

    for (int i = 0; i < SIZE; i++)
    {
        if (i < 9)
        {
            strcat(fieldstr, " ");
        }

        // print row number
        char row[36];
        sprintf(row, "%d |", i + 1);

        for (int j = 0; j < SIZE; j++)
        {
            // print icon
            char val[3];
            sprintf(val, " %c", geticon(field[i][j]));
            strcat(row, val);
        }

        // Return line
        strcat(row, "\n");
        strcat(fieldstr, row);
    }

    printf("%s", fieldstr);

    return 0;
}
