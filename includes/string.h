#ifndef STRING_H
#define STRING_H

#include <string.h>

/// @brief Replace a char from a string by a new char in specific index
/// @param str Initial string
/// @param index Specific index where char will be replaced
/// @param new New char
void replacechar(char *str, int index, char new) {
    int slen = strlen(str);

    for (int i = 0; i < slen; i++)
    {
        if (i == index)
        {
            str[i] = new;
        }
    }
}

#endif