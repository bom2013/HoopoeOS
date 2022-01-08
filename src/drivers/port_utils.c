#include "port_utils.h"

// port byte in\out
unsigned char portReadByte(unsigned short port)
{
    unsigned char res;
    __asm__(
        "in %%dx, %%al"
        : "=a" (res)    // mov the result(al) to res
        : "d" (port)    // set the port(dx) to port
    );
    return res;
}

void portWriteByte(unsigned short port, unsigned char byte)
{
    __asm__(
        "out %%al, %%dx"
        :                           // no input
        : "a" (byte), "d" (port)    // byte to write and port
    );
}

// port word int\out
unsigned short portReadWord(unsigned short port)
{
    unsigned short res;
    __asm__(
        "in %%dx, %%ax"
        : "=a" (res)    // mov the result(al) to res
        : "d" (port)    // set the port(dx) to port
    );
    return res;
}

unsigned short portWriteWord(unsigned short port, unsigned short word)
{
    __asm__(
        "out %%ax, %%dx"
        :                           // no input
        : "a" (word), "d" (port)    // byte to write and port
    );
}
