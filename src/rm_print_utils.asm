; Real mode print utils function
[BITS 16]


; rm_print - print string
; bx - base address of the string
rm_print:
    pusha
    
    rm_print__start:
        ; check for endl
        mov al, [bx]
        cmp al, 0
        je rm_print__end

        ; print char
        mov ah, 0x0e
        int 0x10

        ; inc bx
        inc bx
        jmp rm_print__start
    
    rm_print__end:
        popa
        ret



; rm_print_nl - print new line("\n")
rm_print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret



; rm_print_hex - print number as hex
; dx - number
rm_print_hex:
    pusha

    mov cx, 0
    rm_print_hex__loop:
        cmp cx, 4
        je rm_print_hex__print
        
        ; convert last char of dx to ascii
        mov ax, dx
        and ax, 0x000f ; mask
        add al, 0x30
        cmp al, 0x39
        jle rm_print_hex__insert ; 0-9
        add al, 7 ; A-F

        rm_print_hex__insert:
            ; get the correct position of the string to place our ASCII char
            ; bx <- base address + string length - index of char
            mov bx, HEX_OUT + 5 ; base + length
            sub bx, cx  ; our index variable
            mov [bx], al ; copy the ASCII char on 'al' to the position pointed by 'bx'
            ror dx, 4 ; 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

    ; increment index and loop
    add cx, 1
    jmp rm_print_hex__loop

    rm_print_hex__print:
        mov bx, HEX_OUT
        call rm_print

    popa
    ret

HEX_OUT:
    db '0x0000',0 ; reserve memory for our new string