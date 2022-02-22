// 8259 PIC types and macros definition

#ifndef CPU_DEVICES_PIC_H_
#define CPU_DEVICES_PIC_H_

// Master PIC ports
#define MASTER_PIC_COMMAND_PORT 0x20
#define MASTER_PIC_DATA_PORT 0x21

// Slave PIC ports
#define SLAVE_PIC_COMMAND_PORT 0xA0
#define SLAVE_PIC_DATA_PORT 0xA1

// EOI
#define PIC_EOI 0x20

// Initialization command words
// ICW1
#define ICW1_ICW4 0x01      // ICW4 needed (not needed)
#define ICW1_SINGLE 0x02    // Single mode (cascade)
#define ICW1_INTERVAL4 0x04 // Call address interval 4 (8)
#define ICW1_LEVEL 0x08     // Level triggered mode (edge)
#define ICW1_INIT 0x10      // Initialization - always needed

// ICW3 - master
#define ICW3_MASTER_IRQ0_SLAVE 0x1
#define ICW3_MASTER_IR21_SLAVE 0x2
#define ICW3_MASTER_IRQ2_SLAVE 0x4
#define ICW3_MASTER_IRQ3_SLAVE 0x8
#define ICW3_MASTER_IRQ4_SLAVE 0x10
#define ICW3_MASTER_IRQ5_SLAVE 0x20
#define ICW3_MASTER_IRQ6_SLAVE 0x40
#define ICW3_MASTER_IRQ7_SLAVE 0x80

// ICW3 - slave
#define ICW3_SLAVE_IRQ0 0x0
#define ICW3_SLAVE_IRQ1 0x1
#define ICW3_SLAVE_IRQ2 0x2
#define ICW3_SLAVE_IRQ3 0x3
#define ICW3_SLAVE_IRQ4 0x4
#define ICW3_SLAVE_IRQ5 0x5
#define ICW3_SLAVE_IRQ6 0x6
#define ICW3_SLAVE_IRQ7 0x7

// ICW4
#define ICW4_8086_MODE 0x1          // 80x86 mode (MCS 80/85)
#define ICW4_AUTO_EOI 0x2           // auto EOI (normal)
#define ICW4_SLAVE_BUFFER_MODE 0x8  // slave buffer mode
#define ICW4_MASTER_BUFFER_MODE 0xc // master buffer mode
#define ICW4_SFNM 0x10              // special fully nested mode (sequential)

// Functions

/**
 * Remap PICs vector offset
 *
 * @param masterVectorOffset New vector offset for the master PIC
 * @param slaveVectorOffset New vector offset for the slave PIC
 */
void remapPIC(unsigned char masterVectorOffset, unsigned char slaveVectorOffset);

/**
 * Send EOI to PIC
 *
 * @param irqNumber The irq number
 */
void sendEOI(unsigned char irqNumber);

#endif // CPU_DEVICES_PIC_H_