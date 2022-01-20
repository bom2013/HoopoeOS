#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"

int atoi(const char *str)
{
    int i = 0;
    int sign = 1;
    int base = 0;

    // ignore whitespaces
    while (str[i] == ' ')
    {
        i++;
    }

    // check for sign
    if (str[i] == '+' || str[i] == '-')
    {
        sign = 1 - 2 * (str[i] == '-');
        i++;
    }

    // iterate over digits
    while (isdigit(str[i]))
    {
        base = base * 10 + (str[i] - '0');
        i++;
    }

    return base * sign;
}

char *itoa(int value, char *str, int base)
{
    int i = 0;
    bool isNegative = false;

    // check for zero
    if (value == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    // check for negative number
    if (value < 0)
    {
        isNegative = true;
        // back to positive
        value = -value;
    }

    // iterate over value
    while (value != 0)
    {
        int rem = value % base;
        str[i++] = (rem > 9) ? (rem - 10 + 'a') : (rem + '0');
        value = value / base;
    }

    // add sign if negative
    if (isNegative)
        str[i++] = '-';

    // add null terminator
    str[i] = '\0';

    // reverse str to normal direction
    strrev(str);

    return str;
}