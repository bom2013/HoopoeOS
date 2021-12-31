#!/bin/bash

printMessage () { echo -e "---------------\n$1"; }

{
    # Create env variable
    printMessage "Create some env var"
    export PREFIX="/usr/local/i386elfgcc"
    export PATH="$PREFIX/bin:$PATH"
} && {
    # Compile kernel c files
    printMessage "Compile kernel c files..."
    i386-elf-gcc -ffreestanding -c src/kernel/kernel.c -o bin/kernel/kernel.o -std=c11
} && {
    # Assemble kernel entry
    printMessage "Assemble kernel entry..."
    nasm src/kernel/kernel_entry.asm -f elf -o bin/kernel/kernel_entry.o
} && {
    # Link kernel with kernel entry
    printMessage "Link kernel..."
    i386-elf-ld -o bin/kernel/kernel.bin -Ttext 0x1000 bin/kernel/kernel_entry.o bin/kernel/kernel.o --oformat binary
} && {
    # Assemble boot sector
    printMessage "Assemble boot..."
    nasm -f bin src/boot/boot.asm -o bin/boot/boot.bin -isrc/
} && {
    # Create image file
    printMessage "Create HoopoeOS image file"
    cat bin/boot/boot.bin bin/kernel/kernel.bin > bin/HoopoeOS.bin
} && {
    # Run os image on qemu
    printMessage "Success!"
    read
    
    # check for existence of '-d' debug mode
    if [ $# -eq 0 ]
    then
        timeout --foreground 10 qemu-system-x86_64 -fda bin/HoopoeOS.bin -curses
    else
        qemu-system-x86_64 -fda bin/HoopoeOS.bin -curses -s
    fi
}
