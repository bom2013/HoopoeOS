#ifndef LIBC_STDIO_H_
#define LIBC_STDIO_H_

#include "stdarg.h"

int sprintf(char *result, const char *format, ...);
int vsprintf(char *result, const char *format, va_list arg);

#endif // LIBC_STDIO_H_