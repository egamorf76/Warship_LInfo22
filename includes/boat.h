#include "../includes/vector.h"

int number_boats = 5;
int boats[5] = { 2, 3, 3, 4, 5 };

#define HORIZONTAL 0
#define VERTICAL 1

#ifndef BOAT_H
#define BOAT_H

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

#endif