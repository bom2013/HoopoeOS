// Port utils

#ifndef CPU_PORTS_H_
#define CPU_PORTS_H_

/**
 * Read byte from port
 *
 * @param port The port to read from
 * @return Byte readed from the port
 */
unsigned char portReadByte(unsigned short port);

/**
 * Read word from port
 *
 * @param port The port to read from
 * @return Word readed from the port
 */
unsigned short portReadWord(unsigned short port);

/**
 * Write byte to port
 *
 * @param port The port to write to
 * @param byte Byte to write
 */
void portWriteByte(unsigned short port, unsigned char byte);

/**
 * Write word to port
 *
 * @param port The port to write to
 * @param word Word to write
 */
unsigned short portWriteWord(unsigned short port, unsigned short word);

#endif // CPU_PORTS_H_