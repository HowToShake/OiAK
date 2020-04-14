SYSCALL = 0x80


.code32
.data

jeden: .float -1.111
M_jeden: .long 0
E_jeden: .long 0
S_jeden: .long 0
Ukryty_bit_jeden: .long 0       # ukryta wartosc w przypadkach gdy liczba jest mniejsza od jednego


dwa: .float -1.111
M_dwa: .long 0
E_dwa: .long 0
S_dwa: .long 0
Ukryty_bit_dwa: .long 0

M_wynik: .long 0
E_wynik: .long 0
S_wynik: .long 0
wynik: .float 0

msg: .asciz "\nWynik to: %0.8f \n"
msg_len = . -msg

.text
.global main

PREPARE_RESULT_TO_PRINT:
xorl %edx, %edx
pop %edi
popl %eax
movl %eax, %ebx
movl %eax, %ecx
andl $8388607, %eax
movl $8, %esi
divl %esi
shll $29, %edx
andl $2139095040, %ebx
shrl $23, %ebx
addl $896, %ebx
shll $20, %ebx
andl $-2147483646, %ecx
orl %ecx, %eax
orl %ebx, %eax
pushl %eax
pushl %edx
pushl %edi
ret

main:

PREPARE_VALUES:
movl jeden, %eax            
andl $8388607, %eax         # 838 8607(DEC) = 7F FFFF(HEX) = 0111 1111 1111 1111 1111 1111(BIN) -  pozycje jedynek - max długosc Mantysty 32b.
movl %eax, M_jeden          # przenies odpowiednie wartosci liczby jeden do mantysy

xor %eax, %eax              # kontrolne czyszczenie rejestru

movl dwa, %eax              # tak jak wyzej, przenies w postaci bitowej do mantysy
andl $8388607, %eax
movl %eax, M_dwa

xor %eax, %eax

movl jeden, %eax
andl $2139095040, %eax      # 21 3909 5040(DEC) = 7F80 0000(HEX) = 0111 1111 1000 0000 0000 0000 0000 0000(BIN) - pozycje jedynek - max wartosc Wykladnika 32b.
shrl $23, %eax              # 23(DEC) = 17(HEX) = 0001 0111 - operacja, która ma na celu zostawienie wyłącznie binarnej reprezentacji wykładnika w eax.
movl %eax, E_jeden          

xor %eax, %eax

movl dwa, %eax              # tak samo jak wyżej dla drugiej liczby
andl $2139095040, %eax
shrl $23, %eax
movl %eax, E_dwa    

xor %eax, %eax

movl jeden, %eax
andl $2147483648, %eax      # 21 4748 3648(DEC) = 8000 0000(HEX) = 1000 0000 0000 0000 0000 0000 0000 0000(BIN) - pozycja jedynki - znak liczby zmiennoprzecinkowej 32b.
shrl $31, %eax              # 31(DEC) = 1F(HEX) = 0001 1111(BIN) - przesunięcie tak by w rejestrze zostawić tylko pozycje znaku liczby
movl %eax, S_jeden

xor %eax, %eax

movl dwa, %eax              # tak samo jak powyżej dla drugiej liczby
andl $2147483648, %eax  
shrl $31, %eax
movl %eax, S_dwa

xor %eax, %eax

movl M_jeden, %eax          # przenies wartosc mantysy pierwszej liczby do rejestru eax
orl $8388608, %eax          # 838 8608(DEC) = 80 0000(HEX) = 1000 0000 0000 0000 0000 0000(BIN) - pozycja jedynki - "ukryta jedynka", sprawdzenie czy E nie jest rowne 0
movl %eax, Ukryty_bit_jeden

xor %eax, %eax

movl M_dwa, %eax
orl $8388608, %eax
movl %eax, Ukryty_bit_dwa

xor %eax, %eax


TEST_IS_ZERO:               # sprawdzenie czy obydwie z podanych liczb nie sa zerami
movl jeden, %eax            
xorl dwa, %eax              
cmpl $-2147483648, %eax     # w zapisie 32b -- 1 000 0000 0 000 0000 0000 0000 0000 0000 - kod zera ujemnego 
je QUIT                     #                  S|     E    |            M


COMPARE_EXP:                # porownywanie wykladnikow, tak by mialy one jednakowe wykladniki 
movl E_jeden, %eax
movl E_dwa, %ebx
cmpl %eax, %ebx             # w zaleznosci od porownania przenies sie do:
jg SLIDE_FIRST              # wyrownania wykladnika pierwszej liczby 
je WITHOUT_SLIDE            # nie wyrownuj wykladnikow
jl SLIDE_SECOND             # wyrowna wykladnik drugiej liczby


SLIDE_FIRST:                # procedura wyrownujaca wykladnik pierwszej liczby
incl E_jeden                
movl Ukryty_bit_jeden, %ecx     
shrl %ecx                   # przesuniecie jedynki w prawo = dzielenie przez 2
movl %ecx, Ukryty_bit_jeden     
movl E_jeden, %ecx          
cmpl E_dwa, %ecx            # porownanie wykladnikow
jl SLIDE_FIRST              # jesli wykladnik pierwszy wciaz jest za maly powtorz procedure
movl %ecx, E_wynik          # jesli udalo sie wyrownac wykladniki, przenies rowny wykladnik do wyniku
jmp CHECK_VALUES

SLIDE_SECOND:               # procedura analogiczna dla SLIDE_FIRST, wykonywana na drugiej liczbie
incl E_dwa
movl Ukryty_bit_dwa, %ecx
shrl %ecx
movl %ecx, Ukryty_bit_dwa
movl E_dwa, %ecx
cmpl E_jeden, %ecx
jl SLIDE_SECOND
movl %ecx, E_wynik
jmp CHECK_VALUES

WITHOUT_SLIDE:              # skopiowanie ktoregokolwiek z wykladnikow do wykladnika wyniku.
movl E_dwa, %ecx
movl %ecx, E_wynik


CHECK_VALUES:
movl S_jeden, %ebx
movl S_dwa, %ecx
cmpl %ebx, %ecx             # porownanie czy znaki obydwu liczb sa takie same, jesli tak to przejdz do dodawania
je ADDALGO         

movl Ukryty_bit_jeden, %eax
subl Ukryty_bit_dwa, %eax        
cmpl $0, %eax               # sprawdzenie czy ktoras z podanach liczb nie jest ujemna
jge TEST_IS_NEGATIVE        

negl %eax                   # jezeli jest i jest wieksza od drugiej to wynik bedzie ujemny dlatego mozemy przeniesc znak od razu do wyniku
movl S_jeden, %edx
cmpl $1, %edx               
je CONVERT_RESULT

movl $1, S_wynik
jmp CONVERT_RESULT

ADDALGO:                   # procedura dodawania 
movl Ukryty_bit_jeden, %eax
addl Ukryty_bit_dwa, %eax
movl S_jeden, %edx
cmpl $1, %edx
jne CONVERT_RESULT

movl $1, S_wynik
jmp CONVERT_RESULT


TEST_IS_NEGATIVE:          # procedura sprawdzająca czy dana liczba wyszła ujemna 
movl S_jeden, %edx
cmpl $1, %edx   
jne CONVERT_RESULT         # jeżeli wyszła, to skacz do konwersji wyniku
movl $1, S_wynik

CONVERT_RESULT:            # procedura konwertująca otrzymane wyniki
cmpl $16777216, %eax       # 16777216(DEC) = 100 0000(HEX) = 0001 0000 0000 0000 0000 0000 0000(BIN) - widniejąca jedynka = ukryta jedynka
jl SKIP                    # jeżeli 16777216 jest mniejsze od wartosci w eax, czyli brak ukrytej jedynki skocz do SKIP
shrl $2, %eax              
addl $2, E_wynik


SKIP:                      
cmpl $8388607, %eax        # porownaj  z bitami jedynki na pozycji mantysy
jg CREATE_RESULT
decl E_wynik
shll %eax
jmp CONVERT_RESULT

CREATE_RESULT:             # procedura odpowiedzialna za złożenie w całość poszczególnych składowych liczby zmiennoprzecinkowej
andl $8388607, %eax
movl %eax, M_wynik
movl E_wynik, %edx
shll $23, %edx
orl %eax, %edx
movl %edx, wynik
movl S_wynik, %ebx
cmpl $1, %ebx
jne QUIT

QUIT:
pushl wynik
call PREPARE_RESULT_TO_PRINT
pushl $msg
call printf
movl $1, %eax
movl $0, %ebx
int $SYSCALL
