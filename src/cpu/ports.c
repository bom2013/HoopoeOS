#include "ports.h"
#include "libc/stdint.h"

uint8_t portReadByte(uint16_t port)
{
    uint8_t res;
    __asm__ volatile(
        "inb %%dx, %%al"
        : "=a"(res) // mov the result(al) to res
        : "d"(port) // set the port(dx) to port
    );
    return res;
}

uint16_t portReadWord(uint16_t port)
{
    uint16_t res;
    __asm__ volatile(
        "in %%dx, %%ax"
        : "=a"(res) // mov the result(al) to res
        : "d"(port) // set the port(dx) to port
    );
    return res;
}

void portWriteByte(uint16_t port, uint8_t byte)
{
    __asm__ volatile(
        "outb %%al, %%dx"
        :                      // no input
        : "a"(byte), "d"(port) // byte to write and port
    );
}

void portWriteWord(uint16_t port, uint16_t word)
{
    __asm__ volatile(
        "out %%ax, %%dx"
        :                      // no input
        : "a"(word), "d"(port) // byte to write and port
    );
}
