# src path prefix
BOOT_SRC_PATH = src/boot
KERNEL_SRC_PATH = src/kernel
DRIVERS_SRC_PATH = src/drivers

# bin path prefix
BOOT_BIN_PATH = bin/boot
KERNEL_BIN_PATH = bin/kernel
DRIVERS_BIN_PATH = bin/drivers
DEBUG_BIN_PATH = bin/debug

# wildcards for all .c and .h files
KERNEL_C_SRC_FILES = $(wildcard $(KERNEL_SRC_PATH)/*.c)
DRIVERS_C_SRC_FILES = $(wildcard $(DRIVERS_SRC_PATH)/*.c)
KERNEL_OBJ_FILES := $(patsubst $(KERNEL_SRC_PATH)/%.c,$(KERNEL_BIN_PATH)/%.o,$(KERNEL_C_SRC_FILES))
DRIVERS_OBJ_FILES := $(patsubst $(DRIVERS_SRC_PATH)/%.c,$(DRIVERS_BIN_PATH)/%.o,$(DRIVERS_C_SRC_FILES))
ALL_OBJ = $(KERNEL_OBJ_FILES) $(DRIVERS_OBJ_FILES)

# compilation\linking
CC_PREFIX = /usr/local/i386elfgcc/bin/i386-elf-
CC = $(CC_PREFIX)gcc
LD = $(CC_PREFIX)ld

# some kernel constant
KERNEL_OFFSET = 0x1000


all: HoopoeOS.bin

help:
	@echo "make run - build and run the os"
	@echo "make debug-run - build and run in debug mode"
	@echo "make debug-gdb - run gdb terminal connected to the running os"
	@echo "make debug - build the debug files"
	@echo "make disas - open the disassemble of kernel.c"
	@echo "make clean-build - clean all build files"

run: all
	@timeout --foreground 15 qemu-system-x86_64 -fda bin/HoopoeOS.bin -curses

debug-run: debug
	@qemu-system-x86_64 -fda bin/HoopoeOS.bin -curses -s

debug-gdb: $(DEBUG_BIN_PATH)/kernel.elf
	@gdb -q \
		-ex "target remote localhost:1234" \
		-ex "symbol-file $(DEBUG_BIN_PATH)/kernel.elf"

debug: all $(DEBUG_BIN_PATH)/kernel.elf

disas: bin/kernel.dis
	@nano $^


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
$(KERNEL_OBJ_FILES): $(KERNEL_C_SRC_FILES)
	@echo "[*] Compile kernel c files ($^)"
	@$(CC) -g -std=c11 -ffreestanding -c -o $@ $<

# compile drivers c files
$(DRIVERS_OBJ_FILES): $(DRIVERS_C_SRC_FILES)
	@echo "[*] Compile drivers c files ($^)"
	@$(CC) -g -std=c11 -ffreestanding -c -o $@ $<


# disassemble kernel.bin
bin/kernel.dis: $(KERNEL_BIN_PATH)/kernel.bin
	@echo "[*] Disassemble kernel.bin"
	@ndisasm -b 32 $< > $@

# create kernel.elf for debug symbol
$(DEBUG_BIN_PATH)/kernel.elf: $(KERNEL_BIN_PATH)/kernel_entry.o $(KERNEL_BIN_PATH)/kernel.o
	@echo "[*] Create $@"
	@$(LD) -o $@ -Ttext $(KERNEL_OFFSET) $^

# clean build folders
clean-build:
	@echo "[*] Clean all builds"
	@echo "\t* clean .bin files"
	@find bin -name "*.bin" | xargs rm -rf
	@echo "\t* clean .o files"
	@find bin -name "*.o" | xargs rm -rf
	@echo "\t* clean .dis files"
	@find bin -name "*.dis" | xargs rm -rf
	@echo "\t* clean .elf files"
	@find bin -name "*.elf" | xargs rm -rf