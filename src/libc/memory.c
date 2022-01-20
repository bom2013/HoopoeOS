#include "memory.h"

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