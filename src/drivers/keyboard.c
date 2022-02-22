#include "keyboard.h"
#include "cpu/isr.h"
#include "cpu/ports.h"
#include "cpu/devices/ps2.h"
#include "drivers/screen.h"
#include "libc/stdint.h"
#include "libc/stdlib.h"

static void keyboardInterruptHandler(ISRStackRegisters_t regs)
{
    // Read scancode from PS/2 data port
    uint8_t scancode = portReadByte(PS2_DATA_PORT);

    // Print scancode
    char asciiScancode[10];
    itoa(scancode, asciiScancode, 10);
    kprint("Scancode: ");
    kprint(asciiScancode);
    kprint("\n");
}

void initKeyboard()
{
    // register keyboardInterruptHandler to handle IRQ1
    registerInterruptHandler(IRQ1_GATE_NUMBER, keyboardInterruptHandler);
}