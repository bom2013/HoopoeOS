#include "logging.h"
#include "cpu/devices/serial.h"
#include "drivers/screen.h"
#include "libc/stdio.h"
#include "libc/stdarg.h"
#include "libc/string.h"
#include "drivers/timer.h"

#define MAX_LOGGING_MESSAGE_SIZE (256)

static void log(const char *msg)
{
#ifndef SERIAL_DEBUG
    kprint(msg);
#else
    serial_write_string(msg);
#endif
}

void log_info(const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    char logging_message[MAX_LOGGING_MESSAGE_SIZE];
    sprintf(logging_message, "[INFO] [Ticks: %d] ", get_current_tick());
    strcat(logging_message, msg);
    strcat(logging_message, "\n");

    char formatted_message[MAX_LOGGING_MESSAGE_SIZE];
    vsprintf(formatted_message, logging_message, args);

    log(formatted_message);

    va_end(args);
}

void log_error(const char *msg, const char *src_file, const char *function, int line_number, ...)
{
    va_list args;
    va_start(args, line_number);

    char logging_message[MAX_LOGGING_MESSAGE_SIZE];
    sprintf(logging_message, "[Error] [Ticks: %d | %s in %s:%d]  ", get_current_tick(), src_file, function, line_number);
    strcat(logging_message, msg);
    strcat(logging_message, "\n");
    char formatted_message[MAX_LOGGING_MESSAGE_SIZE];
    vsprintf(formatted_message, logging_message, args);

    log(formatted_message);

    va_end(args);
}