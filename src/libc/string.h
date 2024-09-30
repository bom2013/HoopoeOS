// Simple string.h implementation

#ifndef LIBC_STRING_H_
#define LIBC_STRING_H_

#include "stddef.h"

// Functions - Copying
void *memcpy(void *destination, const void *source, int num);

// Functions - Other
char *strrev(char *str);
size_t strlen(const char *str);

// Types
typedef long unsigned int size_t;

#endif // LIBC_STRING_H_