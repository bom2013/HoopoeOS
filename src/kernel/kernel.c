#include "cpu/isr.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include "cpu/devices/serial.h"
#include "logging.h"

static bool init_kernel()
{
    initTimer(50);
    initKeyboard();
    kclear();
    kprint("[*] Initialize serial\n");
    if (!init_serial(SERIAL_PORT_COM1))
    {
        kprint("[Error] Fail to initialize serial port");
        return false;
    }
    return true;
}

void kmain()
{
    LOG("kmain() start!");
    while (true)
    {
        Key k = readChar();
        char c[2];
        c[0] = toPrintableChar(k);
        c[1] = 0;
        kprint(c);
    }
    LOG("\n[*] kmain() end\n");
}

void _kmain()
{
    ISRInstall();
    __asm__ __volatile__("sti");
    if (!init_kernel())
    {
        // This is best effort, as screen may not work
        ERROR("Fail to initialize kernel");
        return;
    }
    kprint("[*] Enter kmain...\n");
    wait(50);
    kclear();

    kmain();
}
