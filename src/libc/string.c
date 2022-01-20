#include "string.h"
#include "stddef.h"

void *memcpy(void *destination, const void *source, int num)
{
    const char *sourceIndex = (const char *)source;
    char *destinationIndex = (char *)destination;
    while (num--)
    {
        *destinationIndex++ = *sourceIndex++;
    }
    return destination;
}

char *strrev(char *str)
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
    return str;
}

size_t strlen(const char *str)
{
    size_t i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}