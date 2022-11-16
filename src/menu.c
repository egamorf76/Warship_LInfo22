#include "../includes/input.h"
#include "../includes/menu.h"
#include <stdio.h>
#include <conio.h>

int menu() {
    int selected = 0;
    char key;

    while (1)
    {
        key = getch();
        printf("\e[1;1H\e[2J");

        switch (key)
        {
            case UP_ARROW:
                printf("up arrow");
                break;

            case DOWN_ARROW:
                printf("down arrow");
                break;
            
            case ESC:
                return -1;

            default:
                printf("unknow key");
                break;
        }
    }
}

char * printm(int selected) {
    char * messages[2];
    messages[0] = "   Commencer";
    messages[1] = "   Connecter";

    messages[selected][1] = SELECTOR;

    char * result = "";
    for (size_t i = 0; i < 2; i++)
    {
        result += strcat(messages[i], "\n");
    }
    
}