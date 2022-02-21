#include "cpu/isr.h"
#include "drivers/screen.h"
#include "libc/stddef.h"
#include "cpu/timer.h"

void kmain()
{
    ISRInstall();

    kclear();
    kprint("Enter kmain...\n");

    __asm__ __volatile__("sti");
    initTimer(20);
}