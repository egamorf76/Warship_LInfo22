#include "../includes/config.h"
#include "../includes/vector.h"
#include "../includes/math.h"
#include "../includes/boat.h"

/// @brief String to clear console
char *clear = "\e[1;1H\e[2J";

/// @brief String to clear console and print message
char *ownclear = "\e[1;1H\e[2J\nYour field :\n\n";

/// @brief String header
char *header = "\nUse Z / S / Q / D arrows to move, R to rotate, use ENTER to select and ESC to exit :\n\n   | A B C D E F G H I J\n---|--------------------\n";

/// @brief String header
char *headerclear = "\e[1;1H\e[2J\nUse Z / S / Q / D arrows to move, R to rotate, use ENTER to select and ESC to exit :\n\n   | A B C D E F G H I J\n---|--------------------\n";

/// @brief Get icon from state of a case
/// @param status State of the case
/// @return Return a char contains icon
char geticon(int const status)
{
    int sta = status;
    
    if (sta < -1) {
        sta = -1;
    }
    sta++;
    
    return ICONS[clamp(sta, 0, strlen(ICONS) - 1)];
}

void printselected(VECTOR const pos) {
    printf("\n%c%d\n", ALPHABET[pos.X], pos.Y + 1);
}

/// @brief Print of all the field
/// @param field 2D array of the field
/// @param pos Actual selected position
void printfieldselection(int const field[SIZE][SIZE], VECTOR const pos)
{
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
            if (field[i][j] <= SMALL) {
                printf(" ");
            }
            else {
                printf("%c", geticon(field[i][j]));
            }

            //Reset background 
            printf("\033[0m"); 
        }

        //Return line
        printf("\n");
    }
}


/// @brief Draw feild to place boat
/// @param field 2D array of feild
/// @param boat Actual selected boat
void printfieldboat(int const field[SIZE][SIZE], BOAT const boat)
{
    for (int i = 0; i < SIZE; i++) {
        if (i < 9) {
            printf(" ");
        }

        // print row number
        printf("%d |", i + 1); 

        for (int j = 0; j < SIZE; j++) {
            printf(" ");

            if (isboatplace(boat, j, i) == 1) {
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
}

/// @brief Draw own feild
/// @param field 2D array of feild
/// @param boat Actual selected boat
void printownfield(int const field[SIZE][SIZE], char *message)
{
    printf(message);

    for (int i = 0; i < SIZE; i++) {
        if (i < 9) {
            printf(" ");
        }

        // print row number
        printf("%d |", i + 1); 

        for (int j = 0; j < SIZE; j++) {
            printf(" ");

            //print icon
            printf("%c", geticon(field[i][j]));
        }

        //Return line
        printf("\n");
    }
}