#include "idt.h"
#include "libc/stdint.h"

void setIDTGateDescriptor(int descriptorNumber, uint32_t ISREntryPoint)
{
    idt[descriptorNumber].low_offset = GET_LOW16(ISREntryPoint);
    idt[descriptorNumber].selector = KERNEL_CODE_SEGMENT_SELECTOR;
    idt[descriptorNumber].reserved = 0;
    // 1 (Present) 00 (kernel privilege) 0 (Always) 0xE (32-bit interrupt gate) = 0x8E
    idt[descriptorNumber].flags = 0x8E;
    idt[descriptorNumber].high_offset = GET_HIGH16(ISREntryPoint);
}

void loadIDT()
{
    // load the idt array to the idtr
    idtr.offset = (uint32_t)&idt;
    idtr.size = NUMBER_OF_IDT_ENTRIES * sizeof(idt_gate_descriptor_t) - 1;

    // load the IDT
    __asm__ __volatile__("lidtl (%0)" ::"r"(&idtr));
}
