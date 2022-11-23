#include "../includes/config.h"
#include "../includes/vector.h"
#include "../includes/math.h"
#include "draw.c"

/// @brief Start gameloop from 2D array
/// @param field 2D array of the field
/// @return Return status : -1 = error else ok
int gameloop(int field[SIZE][SIZE])
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
                return -1;

            default:
                break;
        }
        selected.X = clamp(selected.X, 0, SIZE - 1);
        selected.Y = clamp(selected.Y, 0, SIZE - 1);
    }
}