#include "actions.c"
#include "selections.c"
#include "../includes/config.h"
#include "../includes/array.h"

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
        if (res != 1)
        {
            printf("\nUn bateau de longueur %d a été coulé\n", res);
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
            boats[i] = selectboat(field, HORIZONTAL, boatslength[i], header);
            result = buildboat(field, boats[i]);

            if (result == -1) { return -1; } //Except if exit
        }
        while (result != 1); //If error : retry
    }
}

/// @brief Start game
/// @return -1 to exit, 0 if error else 1
int start(int ownfield[SIZE][SIZE], int otherfield[SIZE][SIZE], const BOAT otherboats[number_boats]) 
{
    while (isend(otherfield, otherboats) != 1)
    {   
        int res;
        do
        {
            printownfield(ownfield, ownclear);
            res = hit(otherfield, selectposition(otherfield, header));
            
            if (res == -1)
            {
                return -1;
            }
        } 
        while (res != HIT && res != MISSED);
    }
    return 1;
}