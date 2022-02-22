// timer (PIT) types and macros definition

#ifndef CPU_TIMER_H_
#define CPU_TIMER_H_

#include "libc/stdint.h"

#define PIT_BASE_FREQUENCY 1193182

#define PIT_CHANNEL0_PORT 0x40
#define PIT_CHANNEL1_PORT 0x41
#define PIT_CHANNEL2_PORT 0x42
#define PIT_MODE_REGISTER_PORT 0x43

/*
 PIT mode register:
    * Bits 6-7 - Select Channel
    * Bits 4-5 - Access mode
    * Bits 1-3 - Operating mode
    * Bits 0 - BCD mode (binary)
*/

// PIT mode register - Select channel
#define PIT_MODE_REGISTER_SELECT_CHANNEL_0 0x0          // 0 0
#define PIT_MODE_REGISTER_SELECT_CHANNEL_1 0x40         // 0 1
#define PIT_MODE_REGISTER_SELECT_CHANNEL_2 0x80         // 1 0
#define PIT_MODE_REGISTER_SELECT_CHANNEL_READ_BACK 0xc0 // 1 1

// PIT mode register - Access mode
#define PIT_MODE_REGISTER_ACCESS_MODE_LATCH_COUNT 0x0 // 0 0
#define PIT_MODE_REGISTER_ACCESS_MODE_LOBYTE 0x10     // 0 1
#define PIT_MODE_REGISTER_ACCESS_MODE_HIBYTE 0x20     // 1 0
#define PIT_MODE_REGISTER_ACCESS_MODE_BYTE 0x30       // 1 1

// PIT mode register - Operating mode
#define PIT_MODE_REGISTER_OPERATING_MODE_0 0x0 // 0 0 0 - interrupt on terminal count
#define PIT_MODE_REGISTER_OPERATING_MODE_1 0x2 // 0 0 1 - hardware re-triggerable one-shot
#define PIT_MODE_REGISTER_OPERATING_MODE_2 0x4 // 0 1 0 - rate generator
#define PIT_MODE_REGISTER_OPERATING_MODE_3 0x6 // 0 1 1 - square wave generator
#define PIT_MODE_REGISTER_OPERATING_MODE_4 0x8 // 1 0 0 - software triggered strobe
#define PIT_MODE_REGISTER_OPERATING_MODE_5 0xa // 1 0 1 - hardware triggered strobe
#define PIT_MODE_REGISTER_OPERATING_MODE_6 0xc // 1 1 0 - rate generator (same as mode 2)
#define PIT_MODE_REGISTER_OPERATING_MODE_7 0xe // 1 1 1 - square wave generator (same as mode 3)

// PIT mode register - BCD mode (binary)
#define PIT_MODE_REGISTER_BINARY 0x0 // 16-bit binary
#define PIT_MODE_REGISTER_BCD 0x1    // four-digit BCD

/**
 * Init the PIT
 *
 * @param frequency Timer frequency (from ~19Hz)
 */
void initTimer(uint32_t frequency);

/**
 * Wait ticks
 *
 * @param ticks Number of ticks to wait
 */
void wait(uint32_t ticks);

#endif // CPU_TIMER_H_