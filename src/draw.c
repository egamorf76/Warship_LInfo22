#include "../includes/config.h"
#include "../includes/vector.h"
#include "../includes/math.h"
#include "../includes/boat.h"

/// @brief Get icon from state of a case
/// @param status State of the case
/// @return Return a char contains icon
char geticon(int const status)
{
    return ICONS[clamp(status + 1, 0, strlen(ICONS) - 1)];
}

/// @brief print header of field
void printheader() {
    printf("\e[1;1H\e[2J");
    printf("Use UP / DOWN / LEFT / RIGHT arrows to move, R to rotate, use ENTER to select and ESC to exit :\n\n");
    printf("   | A B C D E F G H I J\n");
    printf("---|--------------------\n");
}

/// @brief Print of all the field
/// @param field 2D array of the field
/// @param pos Actual selected position
void printfield(int const field[SIZE][SIZE], VECTOR const pos)
{
    printheader();

    for (int i = 0; i < SIZE; i++) {
        if (i < 9) {
            printf(" ");
        }

        // print row number
        printf("%d |", i + 1); 

        for (int j = 0; j < SIZE; j++) {
            printf(" ");

            if ((pos.X) == j && (pos.Y) == i) {
                //White background at selected position
                printf("\033[37m\033[47m"); 
            }

            //print icon
            printf("%c", geticon(field[i][j]));

            //Reset background 
            printf("\033[0m"); 
        }

        //Return line
        printf("\n");
    }

    //print selected position
    printf("\n%c%d", ALPHABET[pos.X], pos.Y + 1);
}

/// @brief Draw feild to place boat
/// @param field 2D array of feild
/// @param pos Actual selected position
/// @param orientation Actual selected orientation
/// @param length Actual length
void printfieldboat(int const field[SIZE][SIZE], VECTOR const pos, int const orientation, int const length)
{
    printheader();

    for (int i = 0; i < SIZE; i++) {
        if (i < 9) {
            printf(" ");
        }

        // print row number
        printf("%d |", i + 1); 

        for (int j = 0; j < SIZE; j++) {
            printf(" ");

            if (isboatplace(pos, j, i, orientation, length) == 1) {
                //White background at selected position
                printf("\033[37m\033[47m"); 
            }

            //print icon
            printf("%c", geticon(field[i][j]));

            //Reset background 
            printf("\033[0m"); 
        }

        //Return line
        printf("\n");
    }

    //print selected position
    printf("\n%c%d", ALPHABET[pos.X], pos.Y + 1);
}