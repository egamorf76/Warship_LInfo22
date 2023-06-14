#include "menu.c"
#include "server.c"
#include "client.c"


int main(int argc, char const *argv[])
{
    switch (menu())
    {
        case START:
            return startserver();
            break;

        case CONNECT:
            return startconnect();
            break; 
        
        default:
            break;
    }
}
