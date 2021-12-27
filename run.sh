echo "Delete old boot.bin"
rm bin/boot.bin > /dev/null 2>&1

echo "Compile os..."
nasm -f bin src/boot/boot.asm -o bin/boot.bin -isrc/

if [ $? -eq 0 ]; then
    echo "Compilation succeed!"
    read
    timeout --foreground 5 qemu-system-x86_64 -fda bin/boot.bin -curses
else
    echo "Compilation faild!"
fi

