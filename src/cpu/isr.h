// isr types and macros definition

#ifndef CPU_ISR_H_
#define CPU_ISR_H_

#include "libc/stdint.h"

// IRQs number macro
#define IRQ0_GATE_NUMBER 32
#define IRQ1_GATE_NUMBER 33
#define IRQ2_GATE_NUMBER 34
#define IRQ3_GATE_NUMBER 35
#define IRQ4_GATE_NUMBER 36
#define IRQ5_GATE_NUMBER 37
#define IRQ6_GATE_NUMBER 38
#define IRQ7_GATE_NUMBER 39
#define IRQ8_GATE_NUMBER 40
#define IRQ9_GATE_NUMBER 41
#define IRQ10_GATE_NUMBER 42
#define IRQ11_GATE_NUMBER 43
#define IRQ12_GATE_NUMBER 44
#define IRQ13_GATE_NUMBER 45
#define IRQ14_GATE_NUMBER 46
#define IRQ15_GATE_NUMBER 47

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

// Hypervisor Injection Exception
extern void isr28();

// VMM Communication Exception
extern void isr29();

// Security Exception
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

// Interrupt handler function
typedef void (*isr_t)(ISRStackRegisters_t *);

/**
 * Install all the ISRs into the IDT and load it
 */
void ISRInstall();

/**
 * Register ISR handler function to handle specific interrupt
 *
 * @param interruptNumber The interrupt the handler will handle
 * @param handler ISR handler function
 */
void registerInterruptHandler(uint8_t interruptNumber, isr_t handler);

/**
 * Interrupt handler for ISRs 0-31
 *
 * @param regs Registers pushed by interrupt wrapper
 */
void ISRHandler(ISRStackRegisters_t *regs);

/**
 * Interrupt handler for all IRQs, call the specific handler if there is one
 *
 * @param regs Registers pushed by interrupt wrapper
 */
void IRQHandler(ISRStackRegisters_t *regs);

#endif // CPU_ISR_H_