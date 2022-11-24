#include "../includes/vector.h"

#define LENGTH_2_BOAT 1
#define LENGTH_3_BOAT 2
#define LENGTH_4_BOAT 1
#define LENGTH_5_BOAT 1

#define HORIZONTAL 0
#define VERTICAL 1

#ifndef BOAT_H
#define BOAT_H

/// @brief 2D Vector, Orientation and Length of a boat
typedef struct {
    VECTOR Position;
    int Orientation;
    int Length
} BOAT;


/// @brief Check if case shoud be a boat
/// @param pos Selected position
/// @param x Actual X
/// @param y Actual Y
/// @param orientation Actual boat orentation 
/// @param len Actual oat length
/// @return return 0 if not a boat place and 1 if it is a boat position
int isboatplace(BOAT boat, int x, int y) {
    for (int i = 0; i < boat.Length; i++) {
        if (boat.Orientation == HORIZONTAL) {
            if (boat.Position.X + i == x && boat.Position.Y == y) {
                return 1;
            }
        }
        else {
            if (boat.Position.X == x && boat.Position.Y + i == y) {
                return 1;
            }
        }
    }
    return 0;
}

int isalreadyboat(BOAT boat, int x, int y) {
    for (int i = 0; i < boat.Length; i++) {
        if (boat.Orientation == HORIZONTAL) {
            if (boat.Position.X + i == x && boat.Position.Y == y) {
                return 1;
            }
        }
        else {
            if (boat.Position.X == x && boat.Position.Y + i == y) {
                return 1;
            }
        }
    }
    return 0;
}

#endif