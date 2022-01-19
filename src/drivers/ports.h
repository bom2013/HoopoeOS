// Port utils
#ifndef PORTS_H
#define PORTS_H

// port byte in\out
unsigned char portReadByte(unsigned short port);
void portWriteByte(unsigned short port, unsigned char byte);

// port word int\out
unsigned short portReadWord(unsigned short port);
unsigned short portWriteWord(unsigned short port, unsigned short word);

#endif