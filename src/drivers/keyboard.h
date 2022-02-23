// keyboard types and macros definition

#ifndef DRIVERS_KEYBOARD_H_
#define DRIVERS_KEYBOARD_H_

#include "drivers/scancode.h"

#define KEYBOARD_BUFFER_SIZE 256

/**
 * Init the keyboard
 */
void initKeyboard();

/**
 * Get char from buffer
 *
 * @return char from buffer
 */
Key readChar();

#endif // DRIVERS_KEYBOARD_H_
