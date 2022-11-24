#include "menu.c"
#include "game.c"
#include "../includes/config.h"
#include "../includes/array.h"

int main(int argc, char const *argv[])
{
    int field[SIZE][SIZE];
    int orientation = HORIZONTAL;
    int length = 3;
    buildarrays(field, MISSED);

    int id_menu = menu();

    switch (id_menu)
    {
        case START:
            buildboat(field, selectboat(field, orientation, length), orientation, length);
            selectposition(field);
            break;
        
        default:
            break;
    }

}
