#define VGA_BASE_ADDRESS 0xb8000
#define VGA_NUMBER_OF_CHAR 2000

void clear()
{
    char *vgaMemory = (char *)VGA_BASE_ADDRESS;
    for (int i = 0; i < VGA_NUMBER_OF_CHAR; i++)
    {
        vgaMemory[i * 2] = ' ';
    }
}

void kPrintHello()
{
    char *vgaMemory = (char *)VGA_BASE_ADDRESS;
    clear();
    vgaMemory[0] = 'H';
    vgaMemory[2] = 'e';
    vgaMemory[4] = 'l';
    vgaMemory[6] = 'l';
    vgaMemory[8] = 'o';
}

void kmain()
{
    kPrintHello();
}