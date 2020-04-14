	.code32
SYSCALL = 0x80
SYSEXIT = 1
EXIT_SUCCESS = 0
STDOUT = 1
SYSWRITE = 4
SYSREAD = 3
STDIN = 0

input_len = 8
input_end_len = 8
input_mode_len = 8

.data
first: .float 2.00
second: .float 10.00

first_double: .double 0.0
second_double: .double 0.0

input: .space input_len
input_end: .space input_end_len
input_mode: .space input_mode_len

temp: .double 0

.text
welcome_msg: .ascii "Wybierz tryb 1-Dodawanie 2-Odejmowanie 3-Mnozenie 4-Dzielenie : \n"
welcome_msg_len= .-welcome_msg

quit_msg: .ascii "\nWciśnij \"q\", aby zakonczyc program. \n"
quit_msg_len= .-quit_msg

first_msg: .asciz "\nPodaj pierwsza liczbe: "
first_msg_len= .-first_msg

second_msg: .asciz "\nPodaj druga liczbe: "
second_msg_len= .-second_msg

mode: .asciz "\nWybierz obliczenia na 1-pojednycznej precyzji 2-podwojnej precyzji: "
mode_len= .-mode

input_format_float: .asciz "%f"
input_format_double: .asciz "%lf"

printer: .ascii "Wynik to: %f \n"

.global main 

CLEAR:
ffree %st(0)
ffree %st(1)

SKIP: 
ret

PREPARE_RESULT_TO_PRINT:	# Uwaga. Floaty konwertowane sa do doubla(w wyswietlaniu printfem) -- nalezy przekonwertowac z liczby pojedynczej precyzji do podwójnej precyzji
xorl %edx, %edx
pop %edi                   	 # sciagniecie adresu z ostatniej funkcji tak aby pod koniec wrocic do niego -- adres powrotu z ramki stosu
popl %eax

mov temp, %eax		   	# ponizej kopiowanie eax do dwoch osobnych rejestrow by umozliwic "przeskanowanie" calej liczby, tj. 
movl %eax, %ebx			# wyciagniecie znaku, mantysy, wykladnika.
movl %eax, %ecx
				# przygotowanie mantysy do podwojnej precyzji
andl $8388607, %eax		# 8388607(DEC) = 0111 1111 1111 1111 1111 1111(BIN) = długość mantysy w liczbie pojedynczej precyzji (23 bity) -- dzielna (to co dziele)
movl $8, %esi			# 8 (DEC) = 1000(BIN) = dlugosc -- dzielnik (przez co dziele)
divl %esi			# podziel eax przez esi - wynik dzielenia całkowitoliczbowego - eax, reszta z dzielenia - edx.
shll $29, %edx			# 29 (DEC) = 0001 1101‬(BIN). Przesunięcie edx, tak by z prawej strony były same zera - wyrównanie do liczby o podwójnej precyzji.

				#przygotowanie znaku i wykładnika do podwojnej precyzji
andl $2139095040, %ebx		# 2139095040 (DEC) = 0111 1111 1000 0000 0000 0000 0000 0000‬(BIN) - pozycje jedynek = pozycja mantysty w liczbie zmiennoprzecinkowej pojedynczej precyzji
shrl $23, %ebx			# 23 (DEC) = 0001 0111‬(BIN). Przesunięcie pozycji, by wyciągnąć wykładnik.
addl $896, %ebx			# 896 (DEC) = 0011 1000 0000(BIN) Dodanie 896(DEC) by zapisać wykładnik na 11 pozycjach (zgodnie z podwójną precyzją).Obciążenie między formatami.
shll $20, %ebx			# 20 (DEC) = 0001 0100‬(BIN) -- Otrzymujemy wykładnik na liczbie 64 bitowej.

andl $-2147483646, %ecx		# -2147483646 (DEC) = ‭1111 1111 1111 1111 1111 1111 1111 1111 1000 0000 0000 0000 0000 0000 0000 0010‬(BIN) AND i OR -- operacje składające liczbę do postaci 64b.
orl %ecx, %eax
orl %ebx, %eax

pushl %eax			# 1. czesc "double"
pushl %edx			# 2. czesc "double"
pushl %edi			# adres powrotu funkcji
ret



main:

mov $SYSWRITE, %eax             # wybor trybu
mov $STDOUT, %ebx
mov $mode, %ecx
mov $mode_len, %edx
int $SYSCALL

mov $SYSREAD, %eax              # pobrane wartosci trybu
mov $STDIN, %ebx
mov $input_mode, %ecx
mov $input_mode_len, %edx
int $SYSCALL

mov input_mode, %ecx                 # switch case MODE
cmp $0xa31, %ecx
je FLOAT
cmp $0xa32, %ecx
je DOUBLE
JMP QUIT

FLOAT:
mov $SYSWRITE, %eax             # podanie pierwszej liczby
mov $STDOUT, %ebx
mov $first_msg, %ecx
mov $first_msg_len, %edx
int $SYSCALL

push $first
push $input_format_float
call scanf


mov $SYSWRITE, %eax             # podanie drugiej liczby
mov $STDOUT, %ebx
mov $second_msg, %ecx
mov $second_msg_len, %edx
int $SYSCALL

push $second
push $input_format_float
call scanf

mov $SYSWRITE, %eax             # wyswietlenie trybu dodawania/mnozenia/dzielenia/odejmowania
mov $STDOUT, %ebx
mov $welcome_msg, %ecx
mov $welcome_msg_len, %edx
int $SYSCALL

mov $SYSREAD, %eax              # wczytanie trybu od uzytkownika
mov $STDIN, %ebx
mov $input, %ecx
mov $input_len, %edx
int $SYSCALL

mov input, %ecx                 # switch case
cmp $0xa31, %ecx
je F_ADD
cmp $0xa32, %ecx
je F_SUBSTR
cmp $0xa33, %ecx
je F_MULT
cmp $0xa34, %ecx
je F_DIV
JMP QUIT

F_ADD:
fld first                   # zaladuj first liczbe do st(0)
fst %st(1)                  # skopiuj st(0) do st(1)
fld second                  # zaladuj second liczbe do st(0)
faddp %st(1), %st(0)        # dodaj wartosci i zachowaj wynik w st(0)
call SKIP
fstp temp
jmp QUIT

F_SUBSTR:
fld first
fst %st(1)
fld second
fsubp %st(1), %st(0)
call SKIP
fstp temp
jmp QUIT

F_MULT:
fld first
fst %st(1)
fld second
fmulp %st(1), %st(0)
call SKIP
fstp temp
jmp QUIT

F_DIV:
fld first
fst %st(1)
fld second
fdivp %st(1), %st(0)
call SKIP
fstp temp
jmp QUIT



DOUBLE:
mov $SYSWRITE, %eax             # podanie pierwszej liczby
mov $STDOUT, %ebx
mov $first_msg, %ecx
mov $first_msg_len, %edx
int $SYSCALL

push $first_double
push $input_format_double
call scanf


mov $SYSWRITE, %eax             # podanie drugiej liczby
mov $STDOUT, %ebx
mov $second_msg, %ecx
mov $second_msg_len, %edx
int $SYSCALL

push $second_double
push $input_format_double
call scanf

mov $SYSWRITE, %eax             # wyswietlenie trybu dodawania/mnozenia/dzielenia/odejmowania
mov $STDOUT, %ebx
mov $welcome_msg, %ecx
mov $welcome_msg_len, %edx
int $SYSCALL

mov $SYSREAD, %eax              # wczytanie trybu od uzytkownika
mov $STDIN, %ebx
mov $input, %ecx
mov $input_len, %edx
int $SYSCALL

mov input, %ecx                 # switch case
cmp $0xa31, %ecx
je D_ADD
cmp $0xa32, %ecx
je D_SUBSTR
cmp $0xa33, %ecx
je D_MULT
cmp $0xa34, %ecx
je D_DIV
JMP QUIT_D

D_ADD:
                                     # zaladuj first liczbe do st(0)
fldl first_double
fstl %st(1)                         #  skopiuj st(0) do st(1)
fldl second_double                  # zaladuj second liczbe do st(0)

faddp %st(1), %st(0)               # dodaj wartosci i zachowaj wynik w st(0)

call SKIP
fstpl temp
jmp QUIT_D

D_SUBSTR:
fldl first_double
fstl %st(1)
fldl second_double
fsubp %st(1), %st(0)
call SKIP
fstpl temp
jmp QUIT_D

D_MULT:
fldl first_double
fstl %st(1)
fldl second_double
fmulp %st(1), %st(0)
call SKIP
fstpl temp
jmp QUIT_D

D_DIV:
fldl first_double
fstl %st(1)
fldl second_double
fdivp %st(1), %st(0)
call SKIP
fstpl temp
jmp QUIT_D



QUIT:
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $quit_msg, %ecx
mov $quit_msg_len, %edx
int $SYSCALL

mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $input_end, %ecx
mov $input_end_len, %edx
int $SYSCALL

mov input_end, %ecx
cmp $0xa71, %ecx
je EXIT_F
jmp main


QUIT_D:
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $quit_msg, %ecx
mov $quit_msg_len, %edx
int $SYSCALL

mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $input_end, %ecx
mov $input_end_len, %edx
int $SYSCALL

mov input_end, %ecx
cmp $0xa71, %ecx
je EXIT_D
jmp main


EXIT_F:
# fld test
call PREPARE_RESULT_TO_PRINT
push $printer
call printf
call SKIP
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $SYSCALL

EXIT_D:
# fld test
# call PREPARE_RESULT_TO_PRINT
# push $printer
# call printf
call SKIP
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $SYSCALL
