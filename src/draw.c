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
#include "../includes/math.h"

char get_icon(int const status)
{
    return ICONS[clamp(status + 1, 0, strlen(ICONS) - 1)];
}

void draw_field(int const field[SIZE][SIZE])
{
    printf("   | A B C D E F G H I J\n");
    printf("---|--------------------\n");

    for (int i = 0; i < SIZE; i++)
    {
        if (i <= 9)
        {
            printf(" ");
        }

        printf("%d |", i);

        for (int j = 0; j < SIZE; j++)
        {
            char test = get_icon(field[i][j]);
            printf(" %c", test);
        }

        printf("\n");
    }
    
}
