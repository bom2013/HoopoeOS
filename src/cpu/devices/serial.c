#include "serial.h"
#include "cpu/ports.h"
#include "cpu/isr.h"
#include "drivers/screen.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"

#define PORT 0x3f8 // COM1

static void serial_handler(ISRStackRegisters_t *regs)
{
    // TODO: interrupt handler for the serial
}

static bool test_serial(const uint16_t device)
{
    portWriteByte(device + 0, 0xae);
    if (portReadByte(device + 0) != 0xAE)
    {
        return false;
    }
    return true;
}

bool init_serial(const uint16_t device)
{
    // TODO: registerInterruptHandler(SERIAL_IRQ1, serial_handler);

    // Configure
    portWriteByte(device + 1, 0x00);
    portWriteByte(device + 3, 0x80);
    portWriteByte(device + 0, 0x03);
    portWriteByte(device + 1, 0x00);
    portWriteByte(device + 3, 0x03);
    portWriteByte(device + 2, 0xc7);
    portWriteByte(device + 4, 0x0b);
    portWriteByte(device + 4, 0x1e);

    if (!test_serial(device))
    {
        return false;
    }

    portWriteByte(device + 4, 0x0F);

    return true;
}

int serial_received()
{
    return portReadByte(PORT + 5) & 1;
}

char read_serial()
{
    while (serial_received() == 0)
        ;
    return portReadByte(PORT);
}

int is_transmit_empty()
{
    return portReadByte(PORT + 5) & 0x20;
}

void write_serial(char a)
{
    while (is_transmit_empty() == 0)
        ;

    portWriteByte(PORT, a);
}