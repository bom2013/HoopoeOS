#include "cpu/isr.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"

void kInitInterrupts()
{
    ISRInstall();
    __asm__ __volatile__("sti");
    initTimer(50);
    initKeyboard();
}

void kmain()
{
    kclear();
    kInitInterrupts();
    kprint("Enter kmain...\n");
    while (true)
    {
        Key k = readChar();
        char c[2];
        c[0] = toPrintableChar(k);
        c[1] = 0;
        kprint(c);
    }
    kprint("\nend\n");
}