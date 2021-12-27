echo "Delete old boot.bin"
rm bin/boot.bin

echo "Compile os..."
nasm -f bin src/boot.asm -o bin/boot.bin -isrc/

if [ $? -eq 0 ]; then
    echo "Compilation succeed!"
    read
    timeout --foreground 10 qemu-system-x86_64 -nographic -fda bin/boot.bin  
else
    echo "Compilation faild!"
fi

