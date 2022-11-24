#include "menu.c"
#include "game.c"
#include "field.c"
#include "../includes/config.h"
#include "../includes/array.h"

int main(int argc, char const *argv[])
{
    int field[SIZE][SIZE];
    buildarrays(field, EMPTY);

    int id_menu = menu();

    switch (id_menu)
    {
        case START:
            //For each boats build a new one on the field
            for (int i = 0; i < number_boats; i++) {
                int result = buildboat(field, selectboat(field, HORIZONTAL, boats[i]));

                //If error : retry
                while (result != 1) 
                { 
                    if (result == -1) { return 0; } //Except if exit
                    result = buildboat(field, selectboat(field, HORIZONTAL, boats[i]));
                }
            }
            printf("\nRes %d", hit(field, selectposition(field)));
            break;

        case CONNECT:
            break; 
        
        default:
            break;
    }

    printfield(field);
}
