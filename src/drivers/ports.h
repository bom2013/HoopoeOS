// Port utils
#ifndef DRIVERS_PORTS_H_
#define DRIVERS_PORTS_H_

// port byte in\out
unsigned char portReadByte(unsigned short port);
void portWriteByte(unsigned short port, unsigned char byte);

// port word int\out
unsigned short portReadWord(unsigned short port);
unsigned short portWriteWord(unsigned short port, unsigned short word);

#endif // DRIVERS_PORTS_H_