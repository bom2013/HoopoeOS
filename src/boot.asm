[BITS 16] # Real mode - 16 bit
[ORG 0x7c00] # Global offset of 0x7c00

# Infinite loop
jmp $

# Fill (510 - size of previous code) byte with zero
times 510-($-$$) db 0

# Magic number
dw 0xaa55