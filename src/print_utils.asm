; print - print string
; bx - base address of the string
print:
    pusha
    
    print_start:
        ; check for endl
        mov al, [bx]
        cmp al, 0
        je print_end

        ; print char
        mov ah, 0x0e
        int 0x10

        ; inc bx
        inc bx
        jmp print_start
    
    print_end:
        popa
        ret



; print_nl - print new line("\n")
print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret



; print_hex - print number as hex
; dx - number
print_hex:
    pusha

    mov cx, 0
    print_hex_loop:
        cmp cx, 4
        je print_hex_print_hex_out
        
        ; convert last char of dx to ascii
        mov ax, dx
        and ax, 0x000f ; mask
        add al, 0x30
        cmp al, 0x39
        jle insert_char_to_string ; 0-9
        add al, 7 ; A-F

        insert_char_to_string:
            ; get the correct position of the string to place our ASCII char
            ; bx <- base address + string length - index of char
            mov bx, HEX_OUT + 5 ; base + length
            sub bx, cx  ; our index variable
            mov [bx], al ; copy the ASCII char on 'al' to the position pointed by 'bx'
            ror dx, 4 ; 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

    ; increment index and loop
    add cx, 1
    jmp print_hex_loop

    print_hex_print_hex_out:
        mov bx, HEX_OUT
        call print

    popa
    ret

HEX_OUT:
    db '0x0000',0 ; reserve memory for our new string