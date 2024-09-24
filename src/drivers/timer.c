#include "timer.h"
#include "cpu/isr.h"
#include "cpu/ports.h"
#include "drivers/screen.h"
#include "libc/stdint.h"
#include "libc/stdlib.h"

uint32_t timerTicks = 0;

static void timerInterruptHandler(ISRStackRegisters_t *regs)
{
    timerTicks++;
}

void initTimer(uint32_t frequency)
{
    // register timerInterruptHandler to handle IRQ0
    registerInterruptHandler(TIMER_IRQ, timerInterruptHandler);

    // set PIC Divider
    uint32_t divisor = PIT_BASE_FREQUENCY / frequency;
    uint8_t low = GET_LOW8(divisor);
    uint8_t high = GET_HIGH8(divisor);

    // send to PIT
    portWriteByte(PIT_MODE_REGISTER_PORT, PIT_MODE_REGISTER_SELECT_CHANNEL_0 | PIT_MODE_REGISTER_ACCESS_MODE_BYTE | PIT_MODE_REGISTER_OPERATING_MODE_3 | PIT_MODE_REGISTER_BINARY);
    portWriteByte(PIT_CHANNEL0_PORT, low);
    portWriteByte(PIT_CHANNEL0_PORT, high);
}

void wait(uint32_t ticks)
{
    uint32_t endTicks = timerTicks + ticks;
    while (timerTicks < endTicks)
    {
    };
}