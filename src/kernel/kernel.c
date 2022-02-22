#include "cpu/isr.h"
#include "drivers/timer.h"
#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "libc/stddef.h"

void kmain()
{
    ISRInstall();

    kclear();
    kprint("Enter kmain...\n");

    __asm__ __volatile__("sti");
    initKeyboard();
}