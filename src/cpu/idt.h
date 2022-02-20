// idt types and macros definition

#ifndef CPU_IDT_H_
#define CPU_IDT_H_

#include "libc/stdint.h"

/*
 kernel code segment selector calculation:
    Index = 0000000000001 (GDT[1] "Code segment")
    Table Indicator = 0 (gdt, not ldt)
    RPL = 00
    => 0000000000001000 = 0x08
*/
#define KERNEL_CODE_SEGMENT_SELECTOR 0x08

#define NUMBER_OF_IDT_ENTRIES 256

// Types
typedef struct
{
    uint16_t low_offset;
    uint16_t selector;
    uint8_t reserved;
    /*
     Flags:
        Bit 7: Present bit (always 1)
        Bits 6-5: DPL - Privilege of caller
        Bit 4: Always 0
        Bit 3-0: Gate Type (0xE for 32-bit interrupt gate)
    */
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_descriptor_t;

typedef struct
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idt_register_t;

// Variables
idt_gate_descriptor_t idt[NUMBER_OF_IDT_ENTRIES];
idt_register_t idtr;

/**
 * Set IDT gate to ISR
 *
 * @param descriptorNumber IDT gate descriptor number
 * @param ISREntryPoint Entry point of the ISR
 */
void setIDTGateDescriptor(int descriptorNumber, uint32_t ISREntryPoint);

/**
 * Load the IDT
 */
void loadIDT();

#endif // CPU_IDT_H_