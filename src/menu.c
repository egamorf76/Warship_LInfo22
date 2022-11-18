#include "../includes/config.h"
#include "../includes/menu.h"
#include "../includes/math.h"
#include "../includes/string.h"
#include <stdio.h>
#include <conio.h>

int printm(int selected) {
    printf("\e[1;1H\e[2J");
    printf("Use UP / DOWN arrows to move, use ENTER to select and ESC to exit :\n\n");

    char messages[2][25] = { "    Commencer", "    Connecter" };

    replace_char(messages[selected], 2, SELECTOR);

    char result[50] = "";
    for (size_t i = 0; i < 2; i++)
    {
        strcat(result, strcat(messages[i], "\n"));
    }
    printf(result);
}

int menu() {
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