#include "drivers/screen.h"
#include "libc/constant.h"

void kmain()
{
    kclear();
    kprint("Hello World!", NULL);
}