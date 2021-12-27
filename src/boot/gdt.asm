; Simple GDT definition, only code and data segments
gdt_start:
    
    ; first segment must be null segment
    gdt_null_segment:
        dd 0x00000000
        dd 0x00000000
    
    ; code segment
    gdt_code_segment:
        ; Base = 0x00000000, Limit = 0xfffff
        ; Flags = 1 (Gr), 1(Sz), 0(L), 0(Reserved)  -> 1100b
        ; Access Byte = 1(Pr), 00(Privl), 1(S), 1(Ex), 0(DC), 1(RW), 0(Ac) -> 10011010b
        dw 0xffff     ; Limit (0-15 bits)
        dw 0x0000     ; Base (0-15 bits)
        db 0x00       ; Base (16-23 bits)
        db 10011010b  ; Access Byte
        db 11001111b  ; Flags + Limit(16-19 bits)
        db 0x00       ; Base (24-31 bits)
    
    ; data segment
    gdt_data_segment:
        ; Base = 0x00000000, Limit = 0xfffff
        ; Flags = 1 (Gr), 1(Sz), 0(L), 0(Reserved)  -> 1100b
        ; Access Byte = 1(Pr), 00(Privl), 1(S), 0(Ex), 0(DC), 1(RW), 0(Ac) -> 10010010b
        dw 0xffff     ; Limit (0-15 bits)
        dw 0x0000     ; Base (0-15 bits)
        db 0x00       ; Base (16-23 bits)
        db 10010010b  ; Access Byte
        db 11001111b  ; Flags + Limit(16-19 bits)
        db 0x00       ; Base (24-31 bits)

gdt_end:


; GDT descriptor definition
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; size of GDT - 1
    dd gdt_start                ; address of the GDT


; constant for use later
CODE_SEG equ gdt_code_segment - gdt_start
DATA_SEG equ gdt_data_segment - gdt_start