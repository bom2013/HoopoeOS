// Port utils

#ifndef CPU_PORTS_H_
#define CPU_PORTS_H_

#include "libc/stdint.h"

/**
 * Read byte from port
 *
 * @param port The port to read from
 * @return Byte readed from the port
 */
uint8_t portReadByte(uint16_t port);

/**
 * Read word from port
 *
 * @param port The port to read from
 * @return Word readed from the port
 */
uint16_t portReadWord(uint16_t port);

/**
 * Write byte to port
 *
 * @param port The port to write to
 * @param byte Byte to write
 */
void portWriteByte(uint16_t port, uint8_t byte);

/**
 * Write word to port
 *
 * @param port The port to write to
 * @param word Word to write
 */
void portWriteWord(uint16_t port, uint16_t word);

#endif // CPU_PORTS_H_