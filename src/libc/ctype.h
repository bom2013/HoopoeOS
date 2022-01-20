// Simple ctype.h implementation

#ifndef LIBC_CTYPE_H_
#define LIBC_CTYPE_H_

// Character classification functions
int isalnum(int c);
int isalpha(int c);
int isblank(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);

// Character conversion functions
int tolower(int c);
int toupper(int c);

#endif // LIBC_CTYPE_H_