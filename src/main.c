#include "menu.c"
#include "game.c"
#include "../includes/config.h"
#include "../includes/array.h"

int main(int argc, char const *argv[])
{
    // TODO : remake commentary

    int field[SIZE][SIZE];
    int orientation = HORIZONTAL;
    int length = 3;
    buildarrays(field, EMPTY);

    int id_menu = menu();

    switch (id_menu)
    {
        case START:
            buildboat(field, selectboat(field, orientation, length));
            selectposition(field);
            break;
        
        default:
            break;
    }

}
