// Simple stdlib.h implementation

#ifndef LIBC_STDLIB_H_
#define LIBC_STDLIB_H_

// Functions - String conversion
int atoi(const char *str);
char *itoa(int value, char *str, int base);

// Macro constants
#define NULL 0
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Types
typedef long unsigned int size_t;

#endif // LIBC_STDLIB_H_