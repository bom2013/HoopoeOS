#include "keyboard.h"
#include "cpu/isr.h"
#include "cpu/ports.h"
#include "cpu/devices/ps2.h"
#include "drivers/screen.h"
#include "libc/stdint.h"
#include "libc/stdlib.h"
#include "libc/stddef.h"

uint32_t keyboardBufferIndex = 0;
uint32_t keyboardBufferReadIndex = 0;
uint32_t bufferCount = 0;
Key keyboardBuffer[KEYBOARD_BUFFER_SIZE];

static void pushBuffer(Key k)
{
    if (bufferCount < KEYBOARD_BUFFER_SIZE)
    {
        keyboardBuffer[keyboardBufferIndex] = k;
        keyboardBufferIndex = (keyboardBufferIndex + 1) % KEYBOARD_BUFFER_SIZE;
        bufferCount++;
    }
}

static Key popBuffer()
{
    Key res;
    if (bufferCount > 0)
    {
        res = keyboardBuffer[keyboardBufferReadIndex];
        keyboardBufferReadIndex = (keyboardBufferReadIndex + 1) % KEYBOARD_BUFFER_SIZE;
        bufferCount--;
        return res;
    }
    res.scancode = INVALID;
    return res;
}

static void keyboardInterruptHandler(ISRStackRegisters_t *regs)
{
    // Read scancode from PS/2 data port
    uint8_t scancode = portReadByte(PS2_DATA_PORT);
    if (scancode <= 0x59)
    {
        Key k;
        k.scancode = scancode;
        pushBuffer(k);
    }
}

void initKeyboard()
{
    // register keyboardInterruptHandler to handle IRQ1
    registerInterruptHandler(KEYBOARD_IRQ, keyboardInterruptHandler);
}

Key readChar()
{
    Key k;
    do
    {
        k = popBuffer();
    } while (!k.scancode || k.scancode > 0x58);
    return k;
}

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
    if (k.scancode != INVALID)
        return SCANCODE_PRINTABLE_CHAR[k.scancode - 1];
    return 0;
}