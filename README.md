# HoopoeOS
Experimental Tiny Operating System

## Plan (Not necessarily in that order)
- [x] Bootloader
- [x] Switch to protected mode
    - [x] GDT
- [x] C basic kernel
- [x] Basic Drivers
    - [x] Basic IO drivers
        - [x] VGA driver
        - [x] Keyboard
    - [x] Timer
- [x] Interrupt
    - [x] Basic handler
    - [x] IRQ
- [ ] Memory Management
    - [ ] Paging
    - [ ] Kernel Heap
- [ ] Internal Kernel debuger
- [ ] File system
- [ ] User Space
    - [ ] Switch to user mode
    - [ ] System calls
    - [ ] Shell
- [ ] Process managment
    - [ ] Loader
    - [ ] Scheduling
    - [ ] Fork and Execute
- [ ] IPC
- [ ] OS specific compiler
    - [ ] OS Specific Toolchain
    - [ ] libc
- [ ] Advance IO drivers
    - [ ] Mouse keyboard
- [ ] Threads

## How to run
I test the os on qemu, you need:
* gcc and ld for 386
* create conf/config makefile with `HOOPOE_OS_PATH` variable contatin path to project
