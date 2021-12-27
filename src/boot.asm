[BITS 16] ; Real mode - 16 bit
[ORG 0x7c00] ; Global offset of 0x7c00

; save boot drive from dl (BIOS put it there) to global var for later use
mov [BOOT_DRIVE], dl

mov bx, TEST
call rm_print

mov bp, 0x8000
mov sp, bp

mov bx, 0x9000
mov dh, 5
mov dl, [BOOT_DRIVE]
call rm_read_sectors

mov dx, [0x9000]
call rm_print_hex

mov dx, [0x9000+512]
call rm_print_hex

; Infinite loop
jmp $

; Includes
%include "rm_print_utils.asm"
%include "rm_disk_utils.asm"

; Global variables
BOOT_DRIVE: db 0

TEST: db 'test',0
; Fill (510 - size of previous code) byte with zero
times 510-($-$$) db 0

; Magic number
dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface