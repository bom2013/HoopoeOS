// keyboard types and macros definition

#ifndef DRIVERS_KEYBOARD_H_
#define DRIVERS_KEYBOARD_H_

#define KEYBOARD_BUFFER_SIZE 256

typedef enum
{
    // Invalid scancode
    INVALID,
    // Keyboard row 1
    ESC,
    // Keyboard row 2
    NUM1,
    NUM2,
    NUM3,
    NUM4,
    NUM5,
    NUM6,
    NUM7,
    NUM8,
    NUM9,
    NUM0,
    MINUS,
    EQUAL,
    BACKSPACE,
    // Keyboard row 3
    TAB,
    Q,
    W,
    E,
    R,
    T,
    Y,
    U,
    I,
    O,
    P,
    SQUARE_BRACKET_OPEN,
    SQUARE_BRACKET_CLOSE,
    // Keyboard row 4
    ENTER,
    LEFT_CTRL,
    A,
    S,
    D,
    F,
    G,
    H,
    J,
    K,
    L,
    SEMICOLON,
    SINGLE_QUOTE,
    BACK_QUOTE,
    // Keyboard row 5
    LEFT_SHIFT,
    BACK_SLASH,
    Z,
    X,
    C,
    V,
    B,
    N,
    M,
    COMMA,
    DOT,
    SLASH,
    RIGHT_SHIFT,
    // Keyboard row 6
    KEYPAD_ASTERISK,
    LEFT_ALT,
    SPACE,
    CAPSLOCK,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    // Keypad row 1
    NUM_LOCK,
    SCROLL_LOCK,
    // Keypad row 2
    KEYPAD_7,
    KEYPAD_8,
    KEYPAD_9,
    KEYPAD_MINUS,
    // Keypad row 3
    KEYPAD_4,
    KEYPAD_5,
    KEYPAD_6,
    KEYPAD_PLUS,
    // Keypad row 4
    KEYPAD_1,
    KEYPAD_2,
    KEYPAD_3,
    // Keypad row 5
    KEYPAD_0,
    KEYPAD_DOT,
    // Other keys
    F11 = 0x57,
    F12,
} Scancode;

typedef struct
{
    int scancode;
} Key;

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

/**
 * Convert Scancode to printable char
 *
 * @param s Scancode
 * @return Printable char match the scancode or NULL if not printable
 */
char toPrintableChar(Key k);

#endif // DRIVERS_KEYBOARD_H_
