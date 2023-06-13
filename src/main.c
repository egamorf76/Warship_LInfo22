#include "menu.c"
#include "gameengine.c"

int startgame()
{
    BOAT otherboats[number_boats];
    int otherfield[SIZE][SIZE];

    BOAT ownboats[number_boats];
    int ownfield[SIZE][SIZE];

    buildarrays(ownfield, EMPTY);
    buildarrays(otherfield, EMPTY);
    
    placeboats(otherfield, otherboats);
    placeboats(ownfield, ownboats);

    start(ownfield, otherfield, otherboats);

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
