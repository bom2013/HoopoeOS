include test/Makefile

# src path prefix
BOOT_SRC_PATH = src/boot
KERNEL_SRC_PATH = src/kernel
DRIVERS_SRC_PATH = src/drivers
CPU_SRC_PATH = src/cpu
LIBC_SRC_PATH = src/libc
OS_SRC_PATH = src/os

# bin path prefix
BOOT_BIN_PATH = bin/boot
KERNEL_BIN_PATH = bin/kernel
DRIVERS_BIN_PATH = bin/drivers
CPU_BIN_PATH = bin/cpu
LIBC_BIN_PATH = bin/libc
OS_BIN_PATH = bin/os
DEBUG_BIN_PATH = bin/debug

# wildcards for all .c and .h files
KERNEL_C_SRC_FILES = $(wildcard $(KERNEL_SRC_PATH)/*.c)
DRIVERS_C_SRC_FILES = $(wildcard $(DRIVERS_SRC_PATH)/*.c)
CPU_C_SRC_FILES = $(wildcard $(CPU_SRC_PATH)/*.c) $(wildcard $(CPU_SRC_PATH)/*/*.c) 
LIBC_C_SRC_FILES = $(wildcard $(LIBC_SRC_PATH)/*.c)
OS_C_SRC_FILES = $(wildcard $(OS_SRC_PATH)/*.c) $(wildcard $(OS_SRC_PATH)/*/*.c) 

KERNEL_OBJ_FILES = $(patsubst $(KERNEL_SRC_PATH)/%.c,$(KERNEL_BIN_PATH)/%.o,$(KERNEL_C_SRC_FILES))
DRIVERS_OBJ_FILES = $(patsubst $(DRIVERS_SRC_PATH)/%.c,$(DRIVERS_BIN_PATH)/%.o,$(DRIVERS_C_SRC_FILES))
CPU_OBJ_FILES = $(patsubst $(CPU_SRC_PATH)/%.c,$(CPU_BIN_PATH)/%.o,$(CPU_C_SRC_FILES)) $(CPU_BIN_PATH)/interrupt.o
LIBC_OBJ_FILES = $(patsubst $(LIBC_SRC_PATH)/%.c,$(LIBC_BIN_PATH)/%.o,$(LIBC_C_SRC_FILES))
OS_OBJ_FILES = $(patsubst $(OS_SRC_PATH)/%.c,$(OS_BIN_PATH)/%.o,$(OS_C_SRC_FILES))
ALL_OBJ = $(KERNEL_OBJ_FILES) $(DRIVERS_OBJ_FILES) $(CPU_OBJ_FILES) $(CPU_DEVICES_OBJ_FILES) $(LIBC_OBJ_FILES) $(OS_OBJ_FILES)

# compilation\linking
CC_PREFIX = /usr/local/i386elfgcc/bin/i386-elf-
CC = $(CC_PREFIX)gcc
LD = $(CC_PREFIX)ld
CC_OPTION = -Werror -g -std=c11 -ffreestanding -iquote ./src/

# some kernel constant
KERNEL_OFFSET = 0x1000

.PHONY: help, clean-build

all: create-bin-folders HoopoeOS.bin

run: all
	@qemu-system-x86_64 -fda bin/HoopoeOS.bin -curses -serial file:serial.log

run-timeout: all
	@timeout --foreground 15 qemu-system-x86_64 -fda bin/HoopoeOS.bin -curses -serial file:serial.log

run-debug: debug
	@qemu-system-x86_64 -fda bin/HoopoeOS.bin -curses -s

debug-gdb: $(DEBUG_BIN_PATH)/kernel.elf
	@gdb -q \
		-ex "target remote localhost:1234" \
		-ex "symbol-file $(DEBUG_BIN_PATH)/kernel.elf"

debug: all $(DEBUG_BIN_PATH)/kernel.elf

help:
	@echo "make run - build and run the os"
	@echo "make run-timeout - build and run the os with timeout"
	@echo "make run-debug - build and run in debug mode"
	@echo "make debug-gdb - run gdb terminal connected to the running os"
	@echo "make debug - build the debug files"
	@echo "make disas - open the disassemble of kernel.c"
	@echo "make clean-build - clean all build files"

# create build folders
create-bin-folders:
	@(ls bin >> /dev/null 2>&1 || echo "[*] Create bin folders")
	@mkdir -p bin/boot
	@mkdir -p bin/kernel
	@mkdir -p bin/drivers
	@mkdir -p bin/cpu
	@mkdir -p bin/cpu/devices
	@mkdir -p bin/libc
	@mkdir -p bin/debug


disas: bin/kernel.dis
	@nano $^

# clean build folders
clean-build: 
	@echo "[*] Clean all builds"
	@rm -rf bin

# create image file
HoopoeOS.bin: $(BOOT_BIN_PATH)/boot.bin $(KERNEL_BIN_PATH)/kernel.bin
	@echo "[*] Create image file"
	@cat $^ > bin/HoopoeOS.bin

# assemble boot sector
$(BOOT_BIN_PATH)/boot.bin: $(BOOT_SRC_PATH)/boot.asm 
	@echo "[*] Assemble boot sector"
	@nasm -f bin $^ -o $@ -i$(BOOT_SRC_PATH)/

# link kernel obj with kernel entry
$(KERNEL_BIN_PATH)/kernel.bin: $(KERNEL_BIN_PATH)/kernel_entry.o $(ALL_OBJ)
	@echo "[*] Link kernel with kernel entry"
	@$(LD) -o $@ -Ttext $(KERNEL_OFFSET) $^ --oformat binary

# assemble kernel entry
$(KERNEL_BIN_PATH)/kernel_entry.o: $(KERNEL_SRC_PATH)/kernel_entry.asm
	@echo "[*] Assemble kernel entry"
	@nasm -f elf $< -o $@

# compile kernel c files
$(KERNEL_BIN_PATH)/%.o: $(KERNEL_SRC_PATH)/%.c
	@echo "[*] Compile kernel c files ($^)"
	@$(CC) $(CC_OPTION) -c $< -o $@ 

# compile drivers c files
$(DRIVERS_BIN_PATH)/%.o: $(DRIVERS_SRC_PATH)/%.c
	@echo "[*] Compile drivers c files ($^)"
	@$(CC) $(CC_OPTION) -c $< -o $@

# assemble interrupt.asm
$(CPU_BIN_PATH)/interrupt.o: $(CPU_SRC_PATH)/interrupt.asm
	@echo "[*] Assemble interrupt.asm"
	@nasm -f elf $< -o $@

# compile machine-dependent c files
$(CPU_BIN_PATH)/%.o: $(CPU_SRC_PATH)/%.c
	@echo "[*] Compile machine-dependent c files ($^)"
	@$(CC) $(CC_OPTION) -c $< -o $@

# compile libc c files
$(LIBC_BIN_PATH)/%.o: $(LIBC_SRC_PATH)/%.c
	@echo "[*] Compile libc c files ($^)"
	@$(CC) $(CC_OPTION) -c $< -o $@ 

# compile os c files
$(OS_BIN_PATH)/%.o: $(OS_SRC_PATH)/%.c
	@echo "[*] Compile OS c files ($^)"
	@$(CC) $(CC_OPTION) -c $< -o $@ 

# disassemble kernel.bin
bin/kernel.dis: $(KERNEL_BIN_PATH)/kernel.bin
	@echo "[*] Disassemble kernel.bin"
	@ndisasm -b 32 $< > $@

# create kernel.elf for debug symbol
$(DEBUG_BIN_PATH)/kernel.elf: $(KERNEL_BIN_PATH)/kernel_entry.o $(ALL_OBJ)
	@echo "[*] Create $@"
	@$(LD) -o $@ -Ttext $(KERNEL_OFFSET) $^