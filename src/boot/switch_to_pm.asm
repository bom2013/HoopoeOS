; Switch to protected mode
[BITS 16]

switch_to_pm:
    
    ; enable A20 bit
    mov ax, 0x2401
    int 0x15

    ; set vga text mode 3
    mov ax, 0x3
    int 0x10

    ; disable interrupts
    cli
    
    ; load GDT descriptor to GDTR
    lgdt [gdt_descriptor]

    ; turn on cr0
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    ; far-jump to flush cpu pipes
    jmp CODE_SEG:init_pm


; from here we in protected mode
[BITS 32]

; init registers and stack
init_pm:
    ; init registers
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; init stack
    mov ebp, 0x90000
    mov esp, ebp

    jmp BEGIN_PM