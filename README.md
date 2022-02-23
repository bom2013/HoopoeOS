# HoopoeOS
Experimental Tiny Operating System

## Plan (Not necessarily in that order)
- [x] Bootloader
- [x] Moving to protected mode
- [x] C basic kernel
- [x] Basic IO drivers
- [ ] Segmenation
- [ ] Interrupt
- [ ] Paging
- [ ] User mode
- [ ] File system
- [ ] syscalls
- [ ] Basic shell

## How to run
I test the os on qemu, you need:
* gcc and ld for 386
* create conf/config makefile with `HOOPOE_OS_PATH` variable contatin path to project