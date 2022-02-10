; Defined in isr.c
[EXTERN ISRHandler]

; Kernel data segment selector (Index = 2, TI = 0, RPL= 00)
KERNEL_DATA_SEGMENT_SELECTOR equ 0x10

; ISR wrapper
isr_wrapper:
    ; Save CPU state
	pusha                                   ; save edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax, ds
	push eax                                ; save DS
	mov ax, KERNEL_DATA_SEGMENT_SELECTOR    ; kernel data segment selector
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
    ; Call C handler
    cld                     ; clear DF to match sysV ABI to call c function
	call ISRHandler         ; call ISRHandler
	
    ; Restore state
	pop eax                 ; restore DS
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa                    ; restore edi,esi,ebp,esp,ebx,edx,ecx,eax
	add esp, 8              ; cleans up stack used for error code and ISR number
	sti                     ; set interrupt flag
	iret                    ; pops CS, EIP, EFLAGS, SS, and ESP


; ISRs routines
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31


; ISRs routines implementation
; For each routine:
;   1. Clear interrupt flag
;   2. If not pushed by proccesor - push dummy error code
;   3. Push interrupt number
;   4. Jump to isr_wrapper

; isr0 - interrupt number 0 routine
; Division By Zero 
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_wrapper

; isr1 - interrupt number 1 routine
; Debug
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_wrapper

; isr2 - interrupt number 2 routine
; NMI Interrupt
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_wrapper

; isr3 - interrupt number 3 routine
; Breakpoint
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_wrapper

; isr4 - interrupt number 4 routine
; Overflow
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_wrapper

; isr5 - interrupt number 5 routine
; Bound Range Exceeded
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_wrapper

; isr6 - interrupt number 6 routine
; Invalid Opcode
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_wrapper

; isr7 - interrupt number 7 routine
; Device not available
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_wrapper

; isr8 - interrupt number 8 routine
; Double fault
isr8:
    cli
    push byte 8
    jmp isr_wrapper

; isr9 - interrupt number 9 routine
; Coprocessor segment overrun
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_wrapper

; isr10 - interrupt number 10 routine
; Invalid TSS
isr10:
    cli
    push byte 10
    jmp isr_wrapper

; isr11 - interrupt number 11 routine
; Segment not present
isr11:
    cli
    push byte 11
    jmp isr_wrapper

; isr12 - interrupt number 12 routine
; Stack-segment fault
isr12:
    cli
    push byte 12
    jmp isr_wrapper

; isr13 - interrupt number 13 routine
; General protection fault
isr13:
    cli
    push byte 13
    jmp isr_wrapper

; isr14 - interrupt number 14 routine
; Page fault
isr14:
    cli
    push byte 14
    jmp isr_wrapper

; isr15 - interrupt number 15 routine
; Reserved
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_wrapper

; isr16 - interrupt number 16 routine
; x87 FPU error
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_wrapper

; isr17 - interrupt number 17 routine
; Alignment check
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_wrapper

; isr18 - interrupt number 18 routine
; Machine check
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_wrapper

; isr19 - interrupt number 19 routine
; SIMD Floating-Point Exception
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_wrapper

; isr20 - interrupt number 20 routine
; Virtualization
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_wrapper

; isr21 - interrupt number 21 routine
; Control Protection
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_wrapper

; isr22 - interrupt number 22 routine
; Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_wrapper

; isr23 - interrupt number 23 routine
; Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_wrapper

; isr24 - interrupt number 24 routine
; Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_wrapper

; isr25 - interrupt number 25 routine
; Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_wrapper

; isr26 - interrupt number 26 routine
; Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_wrapper

; isr27 - interrupt number 27 routine
; Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_wrapper

; isr28 - interrupt number 28 routine
; Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_wrapper

; isr29 - interrupt number 29 routine
; Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_wrapper

; isr30 - interrupt number 30 routine
; Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_wrapper

; isr31 - interrupt number 31 routine
; Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_wrapper
