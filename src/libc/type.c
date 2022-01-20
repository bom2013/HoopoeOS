#include "type.h"

int isalnum(int c)
{
    return isalpha(c) || isdigit(c);
}

int isalpha(int c)
{
    return isupper(c) || islower(c);
}

int isblank(int c)
{
    // tab, space
    return c == '\t' || c == ' ';
}

int iscntrl(int c)
{
    // NUL, US, DEL
    return c == '\0' || c == 0x1f || c == 0x7f;
}

int isdigit(int c)
{
    // 0-9
    return c >= '0' && c <= '9';
}

int isgraph(int c)
{
    return isprint(c) && c != ' ';
}

int islower(int c)
{
    // a-z
    return c >= 'a' && c <= 'z';
}

int isprint(int c)
{
    // all bigger than US, except DEL
    return c >= 32 && c <= 126;
}

int ispunct(int c)
{
    return isgraph(c) && !isalnum(c);
}

int isspace(int c)
{
    // space (SPC), horizontal tab (TAB), newline (LF), vertical tab (VT), feed (FF), carriage return (CR)
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

int isupper(int c)
{
    // A-Z
    return c >= 'A' && c <= 'Z';
}

int isxdigit(int c)
{
    // 0-9, a-f, A-F
    return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
