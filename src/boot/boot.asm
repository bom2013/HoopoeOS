[BITS 16]

; Global offset of 0x7c00
[ORG 0x7c00]

; kernel load offset
KERNEL_OFFSET equ 0x1000
KERNEL_ALLOCATED_SIZE_ON_DISK equ 30

boot_start:
    ; save boot drive from dl (BIOS put it there) to global var for later use
    mov [BOOT_DRIVE], dl

    ; set the stack
    mov bp, 0x9000
    mov sp, bp

    ; print real mode message
    mov bx, MSG_REAL_MODE
    call rm_print

    ; wait second
    mov bx, 2
    call rm_wait

    ; load kernel from disk
    call load_kernel

    ; switch to protected mode
    call switch_to_pm


; Includes
%include "utils/rm_utils/rm_utils.asm"
%include "utils/pm_utils/pm_utils.asm"
%include "gdt.asm"
%include "switch_to_pm.asm"


[BITS 16]
; load the kernel from disk to KERNEL_OFFSET
load_kernel:
    ; print kernel load message
    mov bx, MSG_KERN_MODE
    call rm_print
    
    ; wait second
    mov bx, 2
    call rm_wait

    ; load kernel from disk
    mov bx, KERNEL_OFFSET                   ; destination
    mov dh, KERNEL_ALLOCATED_SIZE_ON_DISK   ; number of section to read
    mov dl, [BOOT_DRIVE]                    ; drive number
    call rm_read_sectors
    
    ret


; after switch to protected mode
[BITS 32]
BEGIN_PM:
    ; print protected mode message
    mov ebx, MSG_PROT_MODE
    call pm_print
    
    ; jump to kernel entry point
    call KERNEL_OFFSET

    ; infinite loop after kernel done
    jmp $


; Global variables
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16 - bit Real Mode... " , 0
MSG_PROT_MODE db "Successfully landed in 32 - bit Protected Mode" , 0
MSG_KERN_MODE db "Load kernel to memory...", 0

; Fill (510 - size of previous code) byte with zero
times 510-($-$$) db 0

; Magic number
dw 0xaa55
