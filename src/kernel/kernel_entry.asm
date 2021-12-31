; kernel entry point, jump to kmain

; we in protected mode
[BITS 32]

; reference for kmain entry fucntion in kernel.c, linker will resolve this
[extern kmain]

; jump to kmain
call kmain

; infinite loop after kernel done
jmp $
