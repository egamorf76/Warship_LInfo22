#include "menu.c"
#include "game.c"
#include "../includes/config.h"
#include "../includes/array.h"

int main(int argc, char const *argv[])
{
    int field[SIZE][SIZE];
    int length = 3;
    buildarrays(field, EMPTY);

    int id_menu = menu();

    switch (id_menu)
    {
        case START:
            for (int i = 0; i < number_boats; i++) {
                if (buildboat(field, selectboat(field, HORIZONTAL, boats[i])) == -1) {
                    return 0;
                }
            }
            selectposition(field);
            break;

        case CONNECT:
            break; 
        
        default:
            break;
    }

}
