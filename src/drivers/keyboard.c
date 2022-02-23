#include "keyboard.h"
#include "cpu/isr.h"
#include "cpu/ports.h"
#include "cpu/devices/ps2.h"
#include "drivers/screen.h"
#include "drivers/scancode.h"
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

static void keyboardInterruptHandler(ISRStackRegisters_t regs)
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
    registerInterruptHandler(IRQ1_GATE_NUMBER, keyboardInterruptHandler);
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
