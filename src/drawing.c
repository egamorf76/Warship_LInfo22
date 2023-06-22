#pragma once
#include "../includes/config.h"
#include "../includes/vector.h"
#include "../includes/math.h"
#include "../includes/boat.h"

/// @brief Get icon from state of a case
/// @param status State of the case
/// @return Return a char contains icon
char geticon(int const status)
{
    int sta = status;

    if (sta < -1)
    {
        sta = -1;
    }
    sta++;

    return ICONS[clamp(sta, 0, strlen(ICONS) - 1)];
}

/// @brief Print of all the field
/// @param field 2D array of the field
/// @param pos Actual selected position
void printfieldselection(int const field[SIZE][SIZE], VECTOR const pos)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (i < 9)
        {
            printf(" ");
        }

        // print row number
        printf("%d |", i + 1);

        for (int j = 0; j < SIZE; j++)
        {
            printf(" ");

            if ((pos.X) == j && (pos.Y) == i)
            {
                // White background at selected position
                printf("\033[37m\033[47m");
            }

            // print icon
            if (field[i][j] <= SMALL)
            {
                printf(" ");
            }
            else
            {
                printf("%c", geticon(field[i][j]));
            }

            // Reset background
            printf("\033[0m");
        }

        // Return line
        printf("\n");
    }
}

/// @brief Draw feild to place boat
/// @param field 2D array of feild
/// @param boat Actual selected boat
void printfieldboat(int const field[SIZE][SIZE], BOAT const boat)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (i < 9)
        {
            printf(" ");
        }

        // print row number
        printf("%d |", i + 1);

        for (int j = 0; j < SIZE; j++)
        {
            printf(" ");

            if (isboatplace(boat, j, i) == 1)
            {
                // White background at selected position
                printf("\033[37m\033[47m");
            }

            // print icon
            printf("%c", geticon(field[i][j]));

            // Reset background
            printf("\033[0m");
        }

        // Return line
        printf("\n");
    }
}

/// @brief Draw own feild
/// @param fieldstr The string going to be update
/// @param field 2D array of feild
/// @param boat Actual selected boat
void printownfield(char *fieldstr, int const field[SIZE][SIZE], char *message)
{
    strcat(fieldstr, message);

    for (int i = 0; i < SIZE; i++)
    {
        if (i < 9)
        {
            strcat(fieldstr, " ");
        }

        // print row number
        char row[36];
        sprintf(row, "%d |", i + 1);

        for (int j = 0; j < SIZE; j++)
        {
            // print icon
            char val[3];
            sprintf(val, " %c", geticon(field[i][j]));
            strcat(row, val);
        }

        // Return line
        strcat(row, "\n");
        strcat(fieldstr, row);
    }
}