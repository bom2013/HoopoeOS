#include "isr.h"
#include "idt.h"
#include "drivers/screen.h"
#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdlib.h"

void ISRInstall()
{
    setIDTGateDescriptor(0, (uint32_t)isr0);
    setIDTGateDescriptor(1, (uint32_t)isr1);
    setIDTGateDescriptor(2, (uint32_t)isr2);
    setIDTGateDescriptor(3, (uint32_t)isr3);
    setIDTGateDescriptor(4, (uint32_t)isr4);
    setIDTGateDescriptor(5, (uint32_t)isr5);
    setIDTGateDescriptor(6, (uint32_t)isr6);
    setIDTGateDescriptor(7, (uint32_t)isr7);
    setIDTGateDescriptor(8, (uint32_t)isr8);
    setIDTGateDescriptor(9, (uint32_t)isr9);
    setIDTGateDescriptor(10, (uint32_t)isr10);
    setIDTGateDescriptor(11, (uint32_t)isr11);
    setIDTGateDescriptor(12, (uint32_t)isr12);
    setIDTGateDescriptor(13, (uint32_t)isr13);
    setIDTGateDescriptor(14, (uint32_t)isr14);
    setIDTGateDescriptor(15, (uint32_t)isr15);
    setIDTGateDescriptor(16, (uint32_t)isr16);
    setIDTGateDescriptor(17, (uint32_t)isr17);
    setIDTGateDescriptor(18, (uint32_t)isr18);
    setIDTGateDescriptor(19, (uint32_t)isr19);
    setIDTGateDescriptor(20, (uint32_t)isr20);
    setIDTGateDescriptor(21, (uint32_t)isr21);
    setIDTGateDescriptor(22, (uint32_t)isr22);
    setIDTGateDescriptor(23, (uint32_t)isr23);
    setIDTGateDescriptor(24, (uint32_t)isr24);
    setIDTGateDescriptor(25, (uint32_t)isr25);
    setIDTGateDescriptor(26, (uint32_t)isr26);
    setIDTGateDescriptor(27, (uint32_t)isr27);
    setIDTGateDescriptor(28, (uint32_t)isr28);
    setIDTGateDescriptor(29, (uint32_t)isr29);
    setIDTGateDescriptor(30, (uint32_t)isr30);
    setIDTGateDescriptor(31, (uint32_t)isr31);

    // Load idt to idtr
    setIDT();
}

void ISRHandler(ISRStackRegisters_t regs)
{
    char *EXCEPTION_MESSAGE[] = {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "Device not available",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack-segment Fault",
        "General Protection Fault",
        "Page Fault",
        "Reserved",
        "x87 FPU error",
        "Alignment Check",
        "Machine Check",
        "SIMD Floating-Point Exception",
        "Virtualization",
        "Control Protection",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"};

    kprint("received interrupt: ");
    char s[3];
    itoa(regs.interrupt_number, s, 10);
    kprint(s);
    kprint("\n");
    kprint(EXCEPTION_MESSAGE[regs.interrupt_number]);
    kprint("\n");
}