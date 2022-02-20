// isr types and macros definition

#ifndef CPU_ISR_H_
#define CPU_ISR_H_

#include "libc/stdint.h"

// ISRs for first 32 interrupts
// Division By Zero
extern void isr0();

// Debug
extern void isr1();

// NMI Interrupt
extern void isr2();

// Breakpoint
extern void isr3();

// Overflow
extern void isr4();

// Bound Range Exceeded
extern void isr5();

// Invalid Opcode
extern void isr6();

// Device not available
extern void isr7();

// Double fault
extern void isr8();

// Coprocessor segment overrun
extern void isr9();

// Invalid TSS
extern void isr10();

// Segment not present
extern void isr11();

// Stack-segment fault
extern void isr12();

// General protection fault
extern void isr13();

// Page fault
extern void isr14();

// Reserved
extern void isr15();

// x87 FPU error
extern void isr16();

// Alignment check
extern void isr17();

// Machine check
extern void isr18();

// SIMD Floating-Point Exception
extern void isr19();

// Virtualization
extern void isr20();

// Control Protection
extern void isr21();

// Reserved
extern void isr22();

// Reserved
extern void isr23();

// Reserved
extern void isr24();

// Reserved
extern void isr25();

// Reserved
extern void isr26();

// Reserved
extern void isr27();

// Reserved
extern void isr28();

// Reserved
extern void isr29();

// Reserved
extern void isr30();

// Reserved
extern void isr31();

// IRQs
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/*
    Struct for aggregates registers that pushed when isr is called
    The order of pushes (from bottom to up):
        1. Pushed by processor (IA32 Manual 6.1.2.1)
        2. Error code (by proccessor) \ Dummy value (by isr wrapper) and interrupt number (by isr wrapper)
        3. Register pushed using 'pusha' by isr wrapper
        4. DS (by isr wrapper)
*/
typedef struct
{
    uint32_t ds;                                         /* Data segment selector */
    uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax; /* Pushed by pusha. */
    uint32_t interrupt_number, error_code;               /* Interrupt number and error code (if applicable) */
    uint32_t eip, cs, eflags, esp, ss;                   /* Pushed by the processor automatically */
} ISRStackRegisters_t;

void ISRInstall();
void ISRHandler(ISRStackRegisters_t regs);

typedef void (*isr_t)(ISRStackRegisters_t);
void registerInterruptHandler(uint8_t interruptNumber, isr_t handler);
void IRQHandler(ISRStackRegisters_t regs);

#endif // CPU_ISR_H_