#include "pic.h"
#include "cpu/ports.h"

void remapPIC(unsigned char masterVectorOffset, unsigned char slaveVectorOffset)
{
    // ICW1 - init
    portWriteByte(MASTER_PIC_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
    portWriteByte(SLAVE_PIC_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);

    // ICW2 - vector offset
    portWriteByte(MASTER_PIC_DATA_PORT, masterVectorOffset);
    portWriteByte(SLAVE_PIC_DATA_PORT, slaveVectorOffset);

    // ICW3 - master\slave setup
    portWriteByte(MASTER_PIC_DATA_PORT, ICW3_MASTER_IRQ2_SLAVE); // slave PIC at IRQ
    portWriteByte(SLAVE_PIC_DATA_PORT, ICW3_SLAVE_IRQ2);         // slave cascade id = IRQ2

    // ICW4 - some settings
    portWriteByte(MASTER_PIC_DATA_PORT, ICW4_8086_MODE);
    portWriteByte(SLAVE_PIC_DATA_PORT, ICW4_8086_MODE);

    // clean Interrupt Mask Register
    portWriteByte(MASTER_PIC_DATA_PORT, 0x0);
    portWriteByte(SLAVE_PIC_DATA_PORT, 0x0);
}

void sendEOI(unsigned char irqNumber)
{
    // Master - 0-7, Slave - 8-15
    const char NUMBER_OF_MASTER_IRQ = 8;
    const char NUMBER_OF_IRQ = 16;

    // bound check
    if (irqNumber > NUMBER_OF_IRQ)
    {
        // TODO: Add log for error
        return;
    }

    // if irq is from slave we send also to the slave PIC
    if (irqNumber >= NUMBER_OF_MASTER_IRQ)
    {
        portWriteByte(SLAVE_PIC_COMMAND_PORT, PIC_EOI);
    }

    portWriteByte(MASTER_PIC_COMMAND_PORT, PIC_EOI);
}