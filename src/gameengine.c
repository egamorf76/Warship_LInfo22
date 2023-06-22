#pragma once
#include "../includes/array.h"
#include "../includes/config.h"
#include "actions.c"
#include "selections.c"


/// @brief Check if all boats are hit
/// @param field the actual field
/// @param boats all the boats
/// @return if end 1 else 0
int isend(const int field[SIZE][SIZE], const BOAT boats[number_boats]) 
{
    for (size_t i = 0; i < number_boats; i++)
    {
        int res = isboatis(field, boats[i], HIT);
        if (res == 0)
        {
            return 0;
        }
    }

    return 1;
}

int placeboats(int field[SIZE][SIZE], BOAT boats[number_boats])
{
    //For each boats build a new one on the field
    for (int i = 0; i < number_boats; i++) 
    {
        int result;

        do 
        { 
            boats[i] = selectboat(field, HORIZONTAL, boatslength[i], headerclear, "");
            result = buildboat(field, boats[i]);

            if (result == -1) { return -1; } //Except if exit
        }
        while (result != 1); //If error : retry
    }
}

/// @brief Play a round without retry
/// @param ownfield your field
/// @param otherfield the oponent field
/// @return -1 for exit, 0 for error else 1
int playroundnoretry(int ownfield[SIZE][SIZE], int otherfield[SIZE][SIZE])
{
    char message[512];
    printownfield(message, ownfield, ownclear);
    strcat(message, header);
    int res = hit(otherfield, selectposition(otherfield, message, ""));

    return res;
}

/// @brief Play a round
/// @param ownfield your field
/// @param otherfield the oponent field
/// @return -1 for exit, 0 for error else 1
int playround(int ownfield[SIZE][SIZE], int otherfield[SIZE][SIZE])
{
    int res;
    do
    {
        res = playroundnoretry(ownfield, otherfield);
        
        if (res == -1)
        {
            return -1;
        }
    } 
    while (res != HIT && res != MISSED);

    return 1;
}

/// @brief Start game
/// @return -1 to exit, 0 if error else 1
int start(int ownfield[SIZE][SIZE], int otherfield[SIZE][SIZE], const BOAT otherboats[number_boats]) 
{
    while (isend(otherfield, otherboats) != 1)
    {   
        playround(ownfield, otherfield);
    }
    return 1;
}