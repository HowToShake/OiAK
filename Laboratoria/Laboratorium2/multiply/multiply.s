.code32
SYSCALL = 0x80
SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0

.global main

.text
msg: .ascii "Podane liczby to: \n"
msg_len = . -msg
printer: .ascii "Wynik to: %x%x%x%x \n"

.data                                                   # Subsekcja mowiaca "as" zeby zaczal czytac dane od konca -- LittleEndian
                                                        # long -- to samo co int

bufor2: .space 64,                                      # zarezerwowane miejsce w pamięci na drugą liczbę z uwzględniseniem wiodących zer
liczba1:
.long 0x11111111, 0x11111111
liczba1_len = (. - liczba1)/4                        # dlugosc liczby 

liczba2:
.long 0x00000000, 0x00000022
liczba2_len = (. - liczba2)/4     

wynik: .space 64,
wynik_len = (. - wynik)/4 

wynik_offset: .long 0x4

main:
mov $liczba1_len, %edi
mov $liczba2_len, %esi

dec %esi
push $0
firstloop:

mov $liczba1_len, %edi           # 4 "segmenty" liczby1 -- 4 iteracje
dec %edi

clc                              # CF = 0
pushf                            # PUSH Flag register onto stack -- CF Flag

multAlgo:
  clc                            # Zerujemy przeniesienie
  popf                           # Pop Stack into flag

  mov liczba1(,%edi,4), %eax     # Przesunięcie(baza,indeks,mnożnik) baza i indeks -rejestry
  mov liczba2(,%esi,4), %edx
  
  imul %edx            # Dodaj wartości w rejestrach a i b

  pop %ebx
  add %ebx, %eax

  mov $wynik_offset, %ecx
  mov (%ecx), %ecx
  pushf
  mov $liczba1_len, %ebx
 
  sub %ebx, %ecx
  add %edi, %ecx
  inc %ecx
  popf
  
  mov %eax, wynik(,%ecx ,4)                     # Wynik dodawania wrzuć na stos 
  push %edx
  
  pushf                          # I zapisz flagę przeniesienia

  cmp $0, %edi                   # licznik -- jeśli rejestr %edi == 0 to...
  jz carry                   # ...skacz do przeniesienia

  sub $1, %edi                   # Jeśli cmp != 0 to przejdzie tutaj i odejmie od licznika 1
  jmp multAlgo                   # Przeskocz na początek pętli


carry:

  popf                           # Ściągnij flagę przeniesienia ze stosu

  xor %eax, %eax
  xor %ebx, %ebx                 # Wyczyść rejestry 2 wersja.

  pop %edx
  dec %ecx
  adc %edx, wynik(,%ecx ,4)

  mov $wynik_offset, %eax
  mov (%eax), %eax
  dec %eax

  mov $1, %ebx
  mov %eax, wynik_offset(,%ebx,4)
  dec %esi
  cmp $0, %esi

  jle temporary

  jmp firstloop

temporary: 
  mov $wynik_len, %eax

end: 
  mov wynik(,%eax, 4), %ebx
  push %ebx
  dec %eax
  cmp $0, %eax
  jg end
  push $printer                 # dodaj na stos format wyświetlania danych 
  call printf                   # wywołaj funkcję printf do wyświetlenia wyników

exit:
  mov $SYSEXIT, %eax
  mov $EXIT_SUCCESS, %ebx
  int $SYSCALL