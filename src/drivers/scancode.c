#include "scancode.h"
#include "stddef.h"

static const char SCANCODE_PRINTABLE_CHAR[88] = {
    '\e', '1', '2',
    '3', '4', '5', '6',
    '7', '8', '9', '0',
    '-', '=', '\b', '\t',
    'Q', 'W', 'E', 'R',
    'T', 'Y', 'U', 'I',
    'O', 'P', '[', ']',
    '\n', 0, 'A', 'S',
    'D', 'F', 'G', 'H',
    'J', 'K', 'L', ';',
    '\'', '`', 0, '\\',
    'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',',
    '.', '/', 0, '*',
    0, ' ', 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, '7',
    '8', '9', '-', '4',
    '5', '6', '+', '1',
    '2', '3', '0', '.',
    0, 0, 0, 0,
    0};

char toPrintableChar(Key k)
{
    if (k.scancode != IVALID)
        return SCANCODE_PRINTABLE_CHAR[k.scancode-1];
    return 0;
}