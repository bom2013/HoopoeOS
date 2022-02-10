// Simple stdint.h implementation

#ifndef LIBC_STDINT_H_
#define LIBC_STDINT_H_

// Types
typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef int32_t intmax_t;
typedef uint32_t uintmax_t;

// Macro constants
#define INT8_MIN -128
#define INT8_MAX 127
#define UINT8_MAX 255

#define INT16_MIN -32768
#define INT16_MAX 32767
#define UINT16_MAX 65535

#define INT32_MIN -2147483648
#define INT32_MAX 2147483647
#define UINT32_MAX 4294967295

#define INTMAX_MIN INT32_MIN
#define INTMAX_MAX INT32_MAX
#define UINTMAX_MAX UINT32_MAX

// Function-like macros
#define GET_LOW16(address) (uint16_t)((address)&0xFFFF)
#define GET_HIGH16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#endif // LIBC_STDINT_H_