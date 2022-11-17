#include <string.h>

void replace_char(char *str, int index, char new) {
    int slen = strlen(str);

    for (int i = 0; i < slen; i++)
    {
        if (i == index)
        {
            str[i] = new;
        }
    }
}