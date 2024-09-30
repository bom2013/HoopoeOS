#ifndef CPU_DEVICES_SERIAL_H_
#define CPU_DEVICES_SERIAL_H_

#include "libc/stdint.h"
#include "libc/stdbool.h"

#define SERIAL_PORT_COM1 0x3F8
#define SERIAL_PORT_COM2 0x2F8

#define SERIAL_REGISTER_RECEIVE_BUFFER 0
#define SERIAL_REGISTER_TRANSMIT_BUFFER 0
#define SERIAL_REGISTER_INTERRUPT_ENABLE 1
// If DLAB is 1
#define SERIAL_REGISTER_DIVISOR_VALUE_LSB 0
#define SERIAL_REGISTER_DIVISOR_VALUE_MSB 1
// For read
#define SERIAL_REGISTER_INTERRUPT_IDENTIFICATION 2
// For write
#define SERIAL_REGISTER_FIFO_CONTROL_REGISTER 2
// DLAB is the MSB
#define SERIAL_REGISTER_LINE_CONTROL_REGISTER 3
#define SERIAL_REGISTER_MODEM_CONTROL_REGISTER 4
#define SERIAL_REGISTER_LINE_STATUS_REGISTER 5
#define SERIAL_REGISTER_MODEM_STATUS_REGISTER 6
#define SERIAL_REGISTER_SCRATCH_REGISTER 7

#define SERIAL_IRQ1 IRQ3_GATE_NUMBER
#define SERIAL_IRQ2 IRQ3_GATE_NUMBER

bool init_serial(const uint16_t device);

int serial_received();

char serial_read();
int serial_is_transmit_empty();

void serial_write(char c);
void serial_write_string(const char *str);

#endif // CPU_DEVICES_SERIAL_H_
