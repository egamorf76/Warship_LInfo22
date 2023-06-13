#include "menu.c"
#include "gameengine.c"

int startgame()
{
    BOAT boats[number_boats];
    int field[SIZE][SIZE];

    buildarrays(field, EMPTY);
    
    placeboats(field, boats);

    start(field, boats);

    return 1;
}

int main(int argc, char const *argv[])
{
    switch (menu())
    {
        case START:
            return startgame();
            break;

        case CONNECT:
            break; 
        
        default:
            break;
    }
}
