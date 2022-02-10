#include "cpu/isr.h"
#include "drivers/screen.h"
#include "libc/stddef.h"

void kmain()
{
    ISRInstall();
    
    kclear();
    kprint("Enter kmain...\n");

    // Test the interrupt
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}