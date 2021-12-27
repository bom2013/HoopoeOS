echo "Delete old boot.bin"
rm bin/boot.bin

echo "Compile os..."
nasm_output=$(nasm -f bin src/boot.asm -o bin/boot.bin -isrc/ 2>&1)

if [ "${nasm_output}" != '' ]; then
    echo "Compilation faild!"
    echo $nasm_output
else
    echo "Compilation succeed!"
    read
    qemu-system-x86_64 -nographic bin/boot.bin  
fi

