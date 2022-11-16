#include "../includes/status.h"
#include "menu.c"
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int test = HIT;
    printf("status: %d", test);
    scanf("%d", &test);
    printf("status: %d", test);

    menu();
}
