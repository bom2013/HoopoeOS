#ifndef LIBC_STRING_H_
#define LIBC_STRING_H_

#include "constant.h"

void *memcpy(void *destination, const void *source, int num);

char *strrev(char *str);

size_t strlen(const char *str);

#endif // LIBC_STRING_H_