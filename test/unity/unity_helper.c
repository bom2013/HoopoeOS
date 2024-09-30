#include "unity_helper.h"

void reset_buffer(char *buffer, int buffer_size, char *initial_string)
{
    for (size_t i = 0; i < buffer_size; i++)
    {
        buffer[i] = '\0';
    }

    do
    {
        *(buffer++) = *initial_string;
    } while (*(initial_string++));
}