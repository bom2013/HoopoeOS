[BITS 16]

; Global offset of 0x7c00
[ORG 0x7c00]

boot_start:
    ; save boot drive from dl (BIOS put it there) to global var for later use
    mov [BOOT_DRIVE], dl

    ; set the stack
    mov bp, 0x9000
    mov sp, bp

    ; print real mode message
    mov bx, MSG_REAL_MODE
    call rm_print

    ; wait 2 second
    mov bx, 2
    call rm_wait

    ; switch to protected mode
    call switch_to_pm


; Includes
%include "utils/rm_utils/rm_utils.asm"
%include "utils/pm_utils/pm_print_utils.asm"
%include "boot/gdt.asm"
%include "boot/switch_to_pm.asm"


; after switch to protected mode
[BITS 32]
BEGIN_PM:
    ; print protected mode message
    mov ebx, MSG_PROT_MODE
    call pm_print
    
    ; infinite loop
    jmp $


; Global variables
BOOT_DRIVE db 0
MSG_REAL_MODE db " Started in 16 - bit Real Mode " , 0
MSG_PROT_MODE db " Successfully landed in 32 - bit Protected Mode " , 0


; Fill (510 - size of previous code) byte with zero
times 510-($-$$) db 0

; Magic number
dw 0xaa55
