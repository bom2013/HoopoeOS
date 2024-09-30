#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "stdlib.h"

// int is int32 -> max string is '-2147483648' -> max size is 11
#define MAX_ITOA_STR_SIZE (11)
// hex('-2147483648') = '-0x80000000' -> max size is 11
#define MAX_ITOA_HEX_STR_SIZE (11)

int sprintf(char *result, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int return_value = vsprintf(result, format, args);
    va_end(args);
    return return_value;
}

int vsprintf(char *result, const char *format, va_list arg)
{
    const int FAIL = -1;
    if (format == NULL || result == NULL)
    {
        return FAIL;
    }

    size_t format_size = strlen(format);
    char *result_ptr = result;

    for (size_t i = 0; i < format_size; i++)
    {
        if (format[i] != '%')
        {
            *(result_ptr++) = format[i];
            continue;
        }

        if (++i >= format_size)
        {
            return FAIL;
        }

        char *temp_str = NULL;
        char int_string[MAX_ITOA_STR_SIZE] = {'\0'};
        char hex_string[MAX_ITOA_HEX_STR_SIZE] = {'\0'};
        switch (format[i])
        {
        case '%':
            *result_ptr = '%';
            result_ptr++;
            break;
        case 's':
            temp_str = va_arg(arg, char *);
            // we couldn't use strcat because we can't be sure result_ptr is null terminated
            while (*temp_str)
            {
                *(result_ptr++) = *(temp_str++);
            }
            break;
        case 'd':
            // we couldn't use strcat because we can't be sure result_ptr is null terminated
            temp_str = itoa(va_arg(arg, int), int_string, 10);
            while (*temp_str)
            {
                *(result_ptr++) = *(temp_str++);
            }
            break;
        case 'c':
            *result_ptr = va_arg(arg, int);
            result_ptr++;
            break;
        case 'x':
            // we couldn't use strcat because we can't be sure result_ptr is null terminated
            temp_str = itoa(va_arg(arg, int), hex_string, 16);
            while (*temp_str)
            {
                *(result_ptr++) = *(temp_str++);
            }
            break;
        default:
            return FAIL;
        }
    }
    *result_ptr = '\0';
    return result_ptr - result;
}