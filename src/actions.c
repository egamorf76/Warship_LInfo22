#pragma once
#include "../includes/boat.h"
#include "../includes/status.h"
#include "../includes/config.h"

/// @brief Build the boat on the feild from position, orientation and length
/// @param field 2D array of the feild
/// @param boat Actual selected boat
/// @return Return -1 if exit, 0 if error else 1
int buildboat(int field[SIZE][SIZE], BOAT const boat) {
    //If exit
    if (boat.Position.X == -1 && boat.Position.Y == -1) { return -1; }

    //If boat exist at same place
    if (isboatexist(field, boat) == 0) { return 0; }
    
    if (boat.Orientation == HORIZONTAL) {
        for (int i = 0; i < boat.Length; i++) {
            //Affect status at boat's place
            field[boat.Position.Y][boat.Position.X + i] = boatsstatus[i];
        }
    }
    else {
        for (int i = 0; i < boat.Length; i++) {
            //Affect status at boat's place
            field[boat.Position.Y + i][boat.Position.X] = boatsstatus[i];
        }
    }
    return 1;
}

/// @brief Try a shot on field
/// @param field Actuel field
/// @param pos Selected position
/// @return Return -1 if exit, 0 if error or already hit, 1 if Missed and 2 if Hit
int hit(int field[SIZE][SIZE], VECTOR const pos)
{
    // If exit
    if (pos.X == -1 && pos.Y == -1)
    {
        return -1;
    }

    switch (field[pos.Y][pos.X])
    {
    // Already a hit at this place
    case MISSED:
        return 0;
        break;

    case HIT:
        return 0;
        break;

    // Hit in water
    case EMPTY:
        field[pos.Y][pos.X] = MISSED;
        return MISSED;
        break;

    // Hit a boat
    case SMALL:
        field[pos.Y][pos.X] = HIT;
        return HIT;
        break;

    case MEDIUM:
        field[pos.Y][pos.X] = HIT;
        return HIT;
        break;

    case LARGE:
        field[pos.Y][pos.X] = HIT;
        return HIT;
        break;

    case EXTRALARGE:
        field[pos.Y][pos.X] = HIT;
        return HIT;
        break;

    default:
        return 0;
        break;
    }
}