#include "screen.h"
#include "cpu/ports.h"
#include "libc/string.h"
#include "libc/stddef.h"

// Internals functions
int printChar(char c, char attr, int col, int row);
// Offset utils
int getOffsetFromColRow(int col, int row);
int getRowFromOffset(int offset);
int getColFromOffset(int offset);
// Cursor utils
int getCursorOffset();
void setCursorOffset(int offset);

int kprint(const char *message)
{
    return kprintWithAttr(message, NULL);
}

int kprintWithAttr(const char *message, char attr)
{
    return kprintAt(message, attr, -1, -1);
}

int kprintAt(const char *message, char attr, int col, int row)
{
    // get offset from col and row
    int offset;
    if (col < 0 || row < 0)
    {
        offset = getCursorOffset();
        col = getColFromOffset(offset);
        row = getRowFromOffset(offset);
    }
    else
    {
        offset = getOffsetFromColRow(col, row);
    }

    // print message
    int i = 0;
    while (message[i] != '\0')
    {
        offset = printChar(message[i], attr, col, row);
        if (offset == -1)
        {
            return -1;
        }
        col = getColFromOffset(offset);
        row = getRowFromOffset(offset);
        i++;
    }
    return 0;
}

void kclear()
{
    unsigned char *vgaMemory = (unsigned char *)VGA_BASE_ADDRESS;
    const int screenSize = VGA_MAX_COLS * VGA_MAX_ROWS;
    for (int i = 0; i < screenSize; i++)
    {
        // TODO: why not vgaMemory[i] = 0 ?
        vgaMemory[i * 2] = ' ';
        vgaMemory[i * 2 + 1] = VGA_COLOR_CODE_WHITE_ON_BLACK;
    }
    setCursorOffset(getOffsetFromColRow(0, 0));
}

/**
 * Internal function to print char to screen.
 * This function work directly with the video memory
 * Set cursor location to next char offset
 *
 * @param c The char to print
 * @param attr The attribute for the char (if 0 use VGA_COLOR_CODE_WHITE_ON_BLACK)
 * @param row The row to print to (if -1 use current cursor row)
 * @param col The col to print to (if -1 use current cursor col)
 *
 * @return Next char offset or -1 if failed
 */
int printChar(char c, char attr, int col, int row)
{
    // get base video memory address
    unsigned char *vgaMemory = (unsigned char *)VGA_BASE_ADDRESS;

    // set attr
    if (!attr)
        attr = VGA_COLOR_CODE_WHITE_ON_BLACK;

    // check row and col
    if (row >= VGA_MAX_ROWS || col >= VGA_MAX_COLS)
        return -1;

    // get offset
    int offset;
    if (row < 0 || col < 0)
        offset = getCursorOffset();
    else
        offset = getOffsetFromColRow(col, row);

    // print the char
    // if `c` is new line advance offset to new line
    if (c == '\n')
    {
        offset = getOffsetFromColRow(0, getRowFromOffset(offset) + 1);
    }
    // backspace
    else if (c == '\b')
    {
        offset -= 2;
        vgaMemory[offset] = ' ';
        vgaMemory[offset + 1] = attr;
    }
    else
    {
        vgaMemory[offset] = c;
        vgaMemory[offset + 1] = attr;
        offset += 2;
    }

    // if offset overflow the screen scroll down one line
    if (offset >= VGA_MAX_ROWS * VGA_MAX_COLS * 2)
    {
        // copy each line to previous line
        for (int i = 1; i < VGA_MAX_ROWS; i++)
        {
            memcpy(vgaMemory + getOffsetFromColRow(0, i - 1), vgaMemory + getOffsetFromColRow(0, i), VGA_MAX_COLS * 2);
        }

        // clear last line
        unsigned char *lastLineVgaMemory = vgaMemory + getOffsetFromColRow(0, VGA_MAX_ROWS - 1);
        for (int i = 0; i < VGA_MAX_COLS * 2; i++)
        {
            lastLineVgaMemory[i] = 0;
        }

        // move offset to the start of line
        offset -= 2 * VGA_MAX_COLS;
    }

    // set and return the new cursor offset
    setCursorOffset(offset);
    return offset;
}

int getOffsetFromColRow(int col, int row)
{
    return 2 * (row * VGA_MAX_COLS + col);
}

int getRowFromOffset(int offset)
{
    // VGA_MAX_COLS * 2 = number of byte represent full row
    return offset / (2 * VGA_MAX_COLS);
}

int getColFromOffset(int offset)
{
    return (offset - (getRowFromOffset(offset) * (2 * VGA_MAX_COLS))) / 2;
}

int getCursorOffset()
{
    int offset;

    // get high byte of cursor (index 0x0E)
    portWriteByte(VGA_CTRL_PORT, 0x0E);
    offset = portReadByte(VGA_DATA_PORT) << 8;

    // get low byte of cursor (index 0x0F)
    portWriteByte(VGA_CTRL_PORT, 0x0F);
    offset |= portReadByte(VGA_DATA_PORT);

    return offset * 2;
}

void setCursorOffset(int offset)
{
    // normalize offset
    offset /= 2;

    // set high byte of cursor (index 0x0E)
    portWriteByte(VGA_CTRL_PORT, 0x0E);
    portWriteByte(VGA_DATA_PORT, (unsigned char)(offset >> 8));

    // set low byte of cursor(index 0x0F)
    portWriteByte(VGA_CTRL_PORT, 0x0F);
    portWriteByte(VGA_DATA_PORT, (unsigned char)(offset & 0xFF));
}