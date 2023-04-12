#include "../includes/config.h"
#include "../includes/menu.h"
#include "../includes/math.h"
#include "../includes/string.h"
#include "../includes/input.h"
#include <stdio.h>

/// @brief Print menu at selected point
/// @param selected Selected point
void printm(int selected)
{
    printf("\e[1;1H\e[2J");
    printf("Use Z / S arrows to move, use ENTER to select and ESC to exit :\n\n");

    char messages[2][25] = {"    Commencer", "    Connecter"};

    replacechar(messages[selected], 2, SELECTOR);

    char result[50] = "";
    for (int i = 0; i < 2; i++)
    {
        strcat(result, strcat(messages[i], "\n"));
    }
    printf("%s", result);
}

/// @brief Open menu and return selected
/// @return Int of menu selected
int menu()
{
    int selected = 0;
    char key;

    while (1)
    {
        printm(selected);
        key = getch();

        switch (key)
        {
        case UP_ARROW:
            selected--;
            break;

        case DOWN_ARROW:
            selected++;
            break;

        case ESC:
            return -1;

        case ENTER:
            return selected;

        default:
            break;
        }
        selected = clamp(selected, 0, 1);
    }
}