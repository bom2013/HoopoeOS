; kernel entry point, jump to kmain

; we in protected mode
[BITS 32]

; reference for kmain() in kernel.c, linker will resolve this
[extern kmain]

; jump to kmain() in kernel.c
call kmain

; infinite loop after kernel done
jmp $
