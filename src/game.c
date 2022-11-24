#include <stdio.h>
#include "../includes/config.h"
#include "../includes/vector.h"
#include "../includes/math.h"
#include "../includes/status.h"
#include "draw.c"

/// @brief Start gameloop from 2D array to return selected position
/// @param field 2D array of the field
/// @return Return status : -1 = error else ok
VECTOR selectposition(int const field[SIZE][SIZE])
{
    VECTOR selected;
    selected.X = 0;
    selected.Y = 0;
    char key;

    while (1)
    {
        printfield(field, selected);
        key = getch();

        switch (key)
        {
            case UP_ARROW:
                selected.Y--;
                break;

            case DOWN_ARROW:
                selected.Y++;
                break;

            case LEFT_ARROW:
                selected.X--;
                break;

            case RIGHT_ARROW:
                selected.X++;
                break;
            
            case ESC:
                selected.X = -1;
                selected.Y = -1;
                return selected;

            case ENTER:
                return selected;
        }
        selected.X = clamp(selected.X, 0, SIZE - 1);
        selected.Y = clamp(selected.Y, 0, SIZE - 1);
    }
}

/// @brief Print feild to place a boat
/// @param field 2D array of feild
/// @param orientation 0 Horizontal and 1 Vertical
/// @param length Length of the boat
/// @return Return position to start build boat
VECTOR selectboat(int const field[SIZE][SIZE], int * orientation, int const length)
{
    VECTOR selected;
    selected.X = 0;
    selected.Y = 0;
    char key;

    while (1)
    {
        printfieldboat(field, selected, orientation, length);
        key = getch();

        switch (key)
        {
            case UP_ARROW:
                selected.Y--;
                break;

            case DOWN_ARROW:
                selected.Y++;
                break;

            case LEFT_ARROW:
                selected.X--;
                break;

            case RIGHT_ARROW:
                selected.X++;
                break;

            case R:
                if (orientation == HORIZONTAL) {
                    orientation = VERTICAL;
                }
                else {
                    orientation = HORIZONTAL;
                }
                break;
            
            case ESC:
                selected.X = -1;
                selected.Y = -1;
                return selected;

            case ENTER:
                return selected;
        }

        if (orientation == HORIZONTAL) {
            selected.X = clamp(selected.X, 0, SIZE - 3);
            selected.Y = clamp(selected.Y, 0, SIZE - 1);
        }
        else {
            selected.X = clamp(selected.X, 0, SIZE - 1);
            selected.Y = clamp(selected.Y, 0, SIZE - 3);
        }
    }
}

/// @brief Build the boat on the feild from position, orientation and length
/// @param field AD array of the feild
/// @param pos Actual selected position
/// @param orientation Actual selected orintation
/// @param length Actual length
void buildboat(int * field[SIZE][SIZE], VECTOR const pos, int const orientation, int const length) {
    if (orientation == HORIZONTAL) {
        for (int i = 0; i < length; i++) {
            field[pos.Y][pos.X + i] = BOAT;
        }
    }
    else {
        for (int i = 0; i < length; i++) {
            field[pos.Y + i][pos.X] = BOAT;
        }
    }
}