; Protected mode print utils functions
[BITS 32]

; Constants
VGA_BASE_ADDRESS equ 0xb8000
WHITE_ON_BLACK_CHAR_ATTRIBUTE equ 0x0f

; pm_print - print string using VGA
; ebx - base address of the string
pm_print:
    pusha
    mov edx, VGA_BASE_ADDRESS
    pm_print__loop:
        mov al, [ebx]
        mov ah, WHITE_ON_BLACK_CHAR_ATTRIBUTE
        cmp al, 0
        je pm_print__end
        mov [edx], ax
        inc ebx          ; inc to next char
        add edx, 2       ; inc base address to next char entry(+2 bytes)
        jmp pm_print__loop
    pm_print__end:
        popa
        ret
