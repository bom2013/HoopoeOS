#include "cpu/isr.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "libc/stddef.h"

void kInitInterrupt();

void kmain()
{
    ISRInstall();

    kclear();
    kprint("Enter kmain...\n");

    __asm__ __volatile__("sti");
    initKeyboard();
}

void kInitInterrupt()
{
    initTimer(50);
    initKeyboard();
}