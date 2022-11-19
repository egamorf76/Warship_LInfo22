//    | A B C D E F G H I J
// ———|————————————————————
//  1 | # # # # # # # # # #
//  2 | # # # # # # # # # #
//  3 | # # # # # # # # # #
//  4 | # # # # # # # # # #
//  5 | # # # # # # # # # #
//  6 | # # # # # # # # # #
//  7 | # # # # # # # # # #
//  8 | # # # # # # # # # #
//  9 | # # # # # # # # # #
// 10 | # # # # # # # # # #

#include "../includes/config.h"
#include "../includes/vector.h"
#include "../includes/math.h"

char get_icon(int const status)
{
    return ICONS[clamp(status + 1, 0, strlen(ICONS) - 1)];
}

void draw_field(int const field[SIZE][SIZE], VECTOR pos)
{
    printf("\e[1;1H\e[2J");
    printf("Use UP / DOWN / LEFT / RIGHT arrows to move, use ENTER to select and ESC to exit :\n\n");
    printf("   | A B C D E F G H I J\n");
    printf("---|--------------------\n");

    for (int i = 0; i < SIZE; i++)
    {
        if (i < 9)
        {
            printf(" ");
        }

        printf("%d |", i + 1);

        for (int j = 0; j < SIZE; j++)
        {
            char test = get_icon(field[i][j]);
            printf(" ");

            if ((pos.X) == j && (pos.Y) == i)
            {
                printf("\033[37m\033[47m");
            }

            printf("%c", test);

            printf("\033[0m"); 
        }

        printf("\n");
    }
    printf("\n%c%d", ALPHABET[pos.X], pos.Y + 1);
}
