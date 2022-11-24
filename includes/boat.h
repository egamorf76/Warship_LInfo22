#define LENGTH_2_BOAT 1
#define LENGTH_3_BOAT 2
#define LENGTH_4_BOAT 1
#define LENGTH_5_BOAT 1

#define HORIZONTAL 0
#define VERTICAL 1

#ifndef BOAT_H
#define BOAT_H

/// @brief Check if case shoud be a boat
/// @param pos Selected position
/// @param x Actual X
/// @param y Actual Y
/// @param orientation Actual boat orentation 
/// @param len Actual oat length
/// @return return 0 if not a boat place and 1 if it is a boat position
int isboatplace(VECTOR pos, int x, int y, int orientation, int len) {
    for (int i = 0; i < len; i++) {
        if (orientation == HORIZONTAL) {
            if (pos.X + i == x && pos.Y == y) {
                return 1;
            }
        }
        else {
            if (pos.X == x && pos.Y + i == y) {
                return 1;
            }
        }
    }
    return 0;
}

int isalreadyboat(VECTOR pos, int x, int y, int orientation, int len) {
    for (int i = 0; i < len; i++) {
        if (orientation == HORIZONTAL) {
            if (pos.X + i == x && pos.Y == y) {
                return 1;
            }
        }
        else {
            if (pos.X == x && pos.Y + i == y) {
                return 1;
            }
        }
    }
    return 0;
}

#endif