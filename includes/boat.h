#include "../includes/vector.h"
#include "../includes/status.h"

#define HORIZONTAL 0
#define VERTICAL 1

#ifndef BOAT_H
#define BOAT_H

int boats[5] = { 2, 3, 3, 4, 5 };
int number_boats = sizeof boats / sizeof boats[0];
int boatsstatus[5] = { SMALL, MEDIUM, MEDIUM, LARGE, EXTRALARGE };

/// @brief 2D Vector, Orientation and Length of a boat
typedef struct {
    VECTOR Position;
    int Orientation;
    int Length;
} BOAT;


/// @brief Check if case shoud be a boat
/// @param boat Selected boat
/// @param x Actual X
/// @param y Actual Y
/// @return return 0 if not a boat place and 1 if it is a boat position
int isboatplace(BOAT boat, int x, int y) {
    if (boat.Orientation == HORIZONTAL) {
        for (int i = 0; i < boat.Length; i++) {
            if (boat.Position.X + i == x && boat.Position.Y == y) {
                return 1;
            }
        }
    }
    else {
        for (int i = 0; i < boat.Length; i++) {
            if (boat.Position.X == x && boat.Position.Y + i == y) {
                return 1;
            }
        }
    }
    return 0;
}

/// @brief Check if a boat already exist on feild
/// @param field Actual feild
/// @param boat New boat
/// @return 1 if no boat else 0
int isboatexist(int const field[SIZE][SIZE], BOAT const boat) {    
    if (boat.Orientation == HORIZONTAL) {
        for (int i = 0; i < boat.Length; i++) {
            //If Already a boat exist
            if (field[boat.Position.Y][boat.Position.X + i] <= SMALL) {
                return 0;
            }
        }
    }
    else {
        for (int i = 0; i < boat.Length; i++) {
            //If Already a boat exist
            if (field[boat.Position.Y + i][boat.Position.X] <= SMALL) {
                return 0;
            }
        }
    }
    return 1;
}

#endif