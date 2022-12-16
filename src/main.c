#include "menu.c"
#include "gameengine.c"

int main(int argc, char const *argv[])
{
    switch (menu())
    {
        case START:
            return start();
            break;

        case CONNECT:
            break; 
        
        default:
            break;
    }
}
