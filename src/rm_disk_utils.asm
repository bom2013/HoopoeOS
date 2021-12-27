; Real mode disk utils
[BITS 16]


; rm_read_sectors_from_disk - read n sectors from disk start from second sector
; dh - number of sectors to read
; dl - drive
; ES:BX - the destination of the reading
rm_read_sectors:
    pusha
    push dx

    mov al, dh;  number of sectors to read
    mov ch, 0x00 ; cylinder 0
    mov cl, 0x02 ; start from second sector (first sector is the boot sector)
    mov dh, 0x00 ; head 0
    ; dl = drive number

    ; call BIOS interrupt (13h/02)
    mov ah, 0x02 ; Read Disk Sectors
    int 0x13

    ; check for error
    jc rm_read_sectors__disk_error

    ; check if read all sectors
    pop dx
    cmp dh, al
    jne rm_read_sectors__read_error

    rm_read_sectors__end:
        popa
        ret

    rm_read_sectors__disk_error:
        mov bx, DISK_ERROR_MSG
        call rm_print
        jmp rm_read_sectors__end
    
    rm_read_sectors__read_error:
        mov bx, READ_ERROR_MSG
        call rm_print
        jmp rm_read_sectors__end

DISK_ERROR_MSG: 
    db 'Disk read: Error!', 0
READ_ERROR_MSG:
    db 'Disk read: Incorrect number of sectors read!', 0

; TODO: print specific status error message