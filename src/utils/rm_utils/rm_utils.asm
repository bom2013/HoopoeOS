; all rm_utils

%include "utils/rm_utils/rm_print_utils.asm"
%include "utils/rm_utils/rm_disk_utils.asm"

; rm_wait - wait bx second in real mode
; bx - number of second
rm_wait:
    pusha
    
    ; mul cx (0x0f)
    mov cx, 0x0f
    mov ax, bx
    mul cx
    mov cx, ax

    ; mul dx (0x4240)
    mov dx, 0x4240
    mov ax, bx
    mul cx
    mov dx, ax

    ; call BIOS wait function (15h/86h)
    xor ax, ax
    mov ah, 0x86
    int 0x15

    popa
    ret