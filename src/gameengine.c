#include "actions.c"
#include "selections.c"
#include "../includes/config.h"
#include "../includes/array.h"

int isend(int field[SIZE][SIZE], BOAT boats[number_boats]) 
{
    return 0;
}

/// @brief Start game
/// @return -1 to exit, O if error else 1
int start() 
{
    BOAT boats[number_boats];
    int field[SIZE][SIZE];
    buildarrays(field, EMPTY);

    //For each boats build a new one on the field
    for (int i = 0; i < number_boats; i++) 
    {
        int result;

        do 
        { 
            boats[i] = selectboat(field, HORIZONTAL, boatslength[i]);
            result = buildboat(field, boats[i]);

            if (result == -1) { return -1; } //Except if exit
        }
        while (result != 1); //If error : retry
    }
    
    while (isend(field, boats) != 1)
    {   
        int res;
        do
        {
            res = hit(field, selectposition(field));
            
            if (res == -1)
            {
                return -1;
            }
        } 
        while (res != 0);
    }
    return 1;
}