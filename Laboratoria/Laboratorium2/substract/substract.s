.code32
SYSCALL = 0x80
SYSEXIT = 1
EXIT_SUCCESS = 0
STDOUT = 1
SYSWRITE = 4
SYSREAD = 3
STDIN = 0

.global main

.text
msg: .ascii "Wynik to: \n"
msg_len = .- msg
printer: .ascii "Wynik to: %x%x%x%x%x\n"

.data
odjemna:
 .long 0x98765432, 0x98765432, 0x98765432, 0x98765432
odjemna_len = (. - odjemna)/4


odjemnik:
.long 0x11111111, 0x11111111, 0x11111111, 0x11111110
odjemnik_len = (. - odjemnik)/4





main:

    xor %edi, %edi
    mov $odjemnik_len, %edi
    
    clc
    pushf

substractAlgo:

    clc
    popf

    mov odjemnik(,%edi,4), %eax
    mov odjemna(,%edi,4), %ebx

    sbb %eax, %ebx
    push %ebx
    pushf

    cmp $0, %edi
    jz lastCarry

    dec %edi
    jmp substractAlgo

lastCarry:

    popf
    xor %eax, %eax
    xor %ebx, %ebx
    sbb %eax, %ebx
    push %ebx
    jmp end

end:

    push $printer
    call printf

exit:

    mov $SYSEXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $SYSCALL
