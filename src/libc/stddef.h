// Simple stddef.h implementation

#ifndef LIBC_STDDEF_H_
#define LIBC_STDDEF_H_

// Types
typedef long unsigned int size_t;

// Macro constants
#ifndef TEST
#define NULL 0
#endif // TEST

#endif // LIBC_STDDEF_H_