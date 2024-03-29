#pragma once
#include <stdio.h>
#include "../includes/config.h"
#include "../includes/vector.h"
#include "../includes/math.h"
#include "../includes/status.h"
#include "../includes/input.h"
#include "drawing.c"

/// @brief String to clear console
char *clear = "\e[1;1H\e[2J";

/// @brief String to clear console and print message
char *ownclear = "\e[1;1H\e[2J\nYour field :\n\n";

/// @brief String header
char *header = "\nUse Z / S / Q / D arrows to move, R to rotate, use ENTER to select and ESC to exit :\n\n   | A B C D E F G H I J\n---|--------------------\n";

/// @brief String header
char *headerclear = "\e[1;1H\e[2J\nUse Z / S / Q / D arrows to move, R to rotate, use ENTER to select and ESC to exit :\n\n   | A B C D E F G H I J\n---|--------------------\n";

/// @brief Print feild to return selected position
/// @param field 2D array of the field
/// @return Return status : -1 = error else ok
VECTOR selectposition(int const field[SIZE][SIZE], char *headmessage, char *tailmessage) { 
    VECTOR selected;
    selected.X = 4;
    selected.Y = 4;
    char key;

    while (1)
    {
        printf("%s", headmessage);
        printfieldselection(field, selected);
        printf("%s", tailmessage);

        key = getch(); //Wait next key pressed

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
/// @return Return boat struct
BOAT selectboat(int const field[SIZE][SIZE], int const orientation, int const length, char *headmessage, char *tailmessage) {
    VECTOR selected;
    selected.X = 4;
    selected.Y = 4;

    BOAT boat;
    boat.Length = length;
    boat.Position = selected;
    boat.Orientation = orientation;

    char key;

    while (1)
    {
        printf("%s", headmessage);
        printfieldboat(field, boat);
        printf("%s", tailmessage);

        key = getch(); //Wait next key pressed

        switch (key)
        {
            case UP_ARROW:
                boat.Position.Y--;
                break;

            case DOWN_ARROW:
                boat.Position.Y++;
                break;

            case LEFT_ARROW:
                boat.Position.X--;
                break;

            case RIGHT_ARROW:
                boat.Position.X++;
                break;

            case R: //Change rotation of the boat by ressing R key
                if (boat.Orientation == HORIZONTAL) {
                    boat.Orientation = VERTICAL;
                }
                else {
                    boat.Orientation = HORIZONTAL;
                }
                break;
            
            case ESC:
                boat.Position.X = -1;
                boat.Position.Y = -1;
                return boat;

            case ENTER:
                return boat;
        }

        //Clamp selected position in terms of the orientation
        if (boat.Orientation == HORIZONTAL) {
            boat.Position.X = clamp(boat.Position.X, 0, SIZE - boat.Length);
            boat.Position.Y = clamp(boat.Position.Y, 0, SIZE - 1);
        }
        else {
            boat.Position.X = clamp(boat.Position.X, 0, SIZE - 1);
            boat.Position.Y = clamp(boat.Position.Y, 0, SIZE - boat.Length);
        }
    }
}