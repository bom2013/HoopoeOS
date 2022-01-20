#include "drivers/screen.h"
#include "libc/stddef.h"

void kmain()
{
    kclear();
    for(int i=0; i<2000; i++)
        kprint("A", NULL);
    kprint("This will printed on new line\n", NULL);
    kprint("Hello World!", NULL);
}