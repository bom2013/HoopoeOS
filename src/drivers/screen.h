// VGA text mode driver
#ifndef SCREEN_H
#define SCREEN_H

// VGA constants
#define VGA_BASE_ADDRESS 0xb8000
#define VGA_MAX_ROWS 25
#define VGA_MAX_COLS 80

// CRT Controller registers I/O ports
#define VGA_CTRL_PORT 0x3D4
#define VGA_DATA_PORT 0x3D5

// color constants
#define VGA_COLOR_BLACK 0x0
#define VGA_COLOR_BLUE 0x1
#define VGA_COLOR_GREEN 0x2
#define VGA_COLOR_CYAN 0x3
#define VGA_COLOR_RED 0x4
#define VGA_COLOR_MAGENTA 0x5
#define VGA_COLOR_BROWN 0x6
#define VGA_COLOR_LIGHT_GRAY 0x7
#define VGA_COLOR_DARK_GRAY 0x8
#define VGA_COLOR_LIGHT_BLUE 0x9
#define VGA_COLOR_LIGHT_GREEN 0xa
#define VGA_COLOR_LIGHT_CYAN 0xb
#define VGA_COLOR_LIGHT_RED 0xc
#define VGA_COLOR_LIGHT_PINK 0xd
#define VGA_COLOR_LIGHT_YELLOW 0xe
#define VGA_COLOR_LIGHT_WHITE 0xf
// macro to create color code
#define VGA_COLOR_CODE(backgroundColor, foregroundColor) ((((unsigned char)backgroundColor) << 4) | (foregroundColor))
// usful color codes
#define VGA_COLOR_CODE_WHITE_ON_BLACK VGA_COLOR_CODE(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_WHITE)
#define VGA_COLOR_CODE_RED_ON_BLACK VGA_COLOR_CODE(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_RED)

// public API

/**
 * Print message to screen
 * 
 * @param message The message to print
 * @param attr Print attribute, if null use VGA_COLOR_CODE_WHITE_ON_BLACK
 * @return 0 if success or -1 if fail
 */
int kprint(char *message, char attr);

/**
 * Print message to screen at `row` and `col`
 * 
 * @param message The message to print
 * @param col The column (between 0 and MAX_COL-1), if negative use current offset
 * @param row The row (between 0 and MAX_ROW-1), if negative use current offset
 * @param attr Print attribute, if null use VGA_COLOR_CODE_WHITE_ON_BLACK
 * @return 0 if success or -1 if fail
 */
int kprintAt(char *message, char attr, int col, int row);

/**
 * Clear the screen
 */
void kclear();

#endif