#include "menu.c"
#include "game.c"
#include "../includes/config.h"

int main(int argc, char const *argv[])
{
    int field[SIZE][SIZE] = 
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, -1, 0, 0, 0, 1, 0, 0, 1, 0},
        { 5, 0, 4, 4, 4, 4, 0, 0, 1, 0},
        { 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 5, 0, 1, 0, -1, 0, 0, 0, 0, 0},
        { 5, 0, 0, 0, 0, 0, 0, 0, 3, 0},
        { 5, 0, 0, 0, 0, 0, 0, 0, 3, 0},
        { 0, 0, -1, 0, 0, 2, 2, 0, 3, 0},
        { 0, 3, 3, 3, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    int id_menu = menu();

    switch (id_menu)
    {
    case START:
        gameloop(field);
        break;
    
    default:
        break;
    }

}
