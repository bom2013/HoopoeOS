# src path prefix
BOOT_SRC_PATH = src/boot
KERNEL_SRC_PATH = src/kernel

# bin path prefix
BOOT_BIN_PATH = bin/boot
KERNEL_BIN_PATH = bin/kernel

# compilation\linking
CC_PREFIX = /usr/local/i386elfgcc/bin/i386-elf-
CC = $(CC_PREFIX)gcc
LD = $(CC_PREFIX)ld


all: HoopoeOS.bin

run: all
	timeout --foreground 15 qemu-system-x86_64 -fda bin/HoopoeOS.bin -curses

run-debug:
	qemu-system-x86_64 -fda bin/HoopoeOS.bin -curses -s

disas: bin/kernel.dis
	nano $^

# create image file
HoopoeOS.bin: $(BOOT_BIN_PATH)/boot.bin $(KERNEL_BIN_PATH)/kernel.bin
	cat $^ > bin/HoopoeOS.bin

# assemble boot sector
$(BOOT_BIN_PATH)/boot.bin: $(BOOT_SRC_PATH)/boot.asm 
	nasm -f bin $^ -o $@ -i$(BOOT_SRC_PATH)/

# link kernel with kernel entry
$(KERNEL_BIN_PATH)/kernel.bin: $(KERNEL_BIN_PATH)/kernel_entry.o $(KERNEL_BIN_PATH)/kernel.o
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# assemble kernel entry
$(KERNEL_BIN_PATH)/kernel_entry.o: $(KERNEL_SRC_PATH)/kernel_entry.asm
	nasm -f elf $< -o $@

# compile c kernel files
$(KERNEL_BIN_PATH)/kernel.o: $(KERNEL_SRC_PATH)/kernel.c
	$(CC) -std=c11 -ffreestanding -c $^ -o $@


# disassemble kernel.c
bin/kernel.dis: $(KERNEL_BIN_PATH)/kernel.bin
	ndisasm -b 32 $< > $@

# clean build folders
clean-build:
	find bin -name "*.bin" | xargs rm -rf
	find bin -name "*o" | xargs rm -rf