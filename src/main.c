#include "menu.c"


int main(int argc, char const *argv[])
{
    switch (menu())
    {
        case START:
            //return startserver();
            break;

        case CONNECT:
            //return startconnect();
            break; 
        
        default:
            break;
    }
}
