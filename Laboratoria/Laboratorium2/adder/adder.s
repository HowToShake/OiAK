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
printer: .ascii "Wynik to: %x%x%x%x%x%x%x%x\n"

.data                                                   #Subsekcja mowiaca "as" zeby zaczal czytac dane od konca -- LittleEndian
                                                        #long -- to samo co int

bufor2: .space 64,                                      # zarezerwowane miejsce w pamięci na drugą liczbę z uwzględnieniem wiodących zer
liczba1:
.long 0x11111111, 0x11111111, 0x11111111, 0x11111112, 0x12345678, 0x12345678, 0x12345678, 0x12345678  
liczba1_len = (. - liczba1)/4                           # dlugosc liczby 

liczba2:
.long 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111

liczba2_len = (. - liczba2)/4

main:

mov $liczba2_len, %edi          # edi = rozmiar 2 liczby         
dec %edi                        # edi--
equalNumbers:

  mov liczba2(,%edi,4), %eax    # skopiuj  fragment wartosci liczby 2 do eax 
  mov bufor2(,%edi,4), %ebx     # skopiuj zera z bufora -- domyslnie ustawiany na zera przez gcc

  adc %eax, %ebx                # dodaj wartosc 

  mov %ebx, bufor2(,%edi,4)     # wynik dodawania dodaj do bufora 

  cmp $0, %edi                  # sprawdzenie czy przeiterowalismy po dlugosci calej liczby
  jz process

  sub $1, %edi


jmp equalNumbers



process:
xor %edi, %edi			 #zerowanie rejestru
mov $liczba1_len, %edi           #4 "segmenty" liczby1 -- 4 iteracje
clc                              #CF = 0
pushf                            #PUSH Flag register onto stack -- CF Flag

addAlgo:
  clc                            #Zerujemy przeniesienie
  popf                           #Pop Stack into flag

  mov liczba1(,%edi,4), %eax     #Przesunięcie(baza,indeks,mnożnik) baza i indeks -rejestry
  mov bufor2(,%edi,4), %ebx

  adc %eax, %ebx                 #Dodaj wartości w rejestrach a i b

  push %ebx                      #Wynik dodawania wrzuć na stos 

  pushf                          #I zapisz flagę przeniesienia

  cmp $0, %edi                   #licznik -- jeśli rejestr %edi == 0 to...
  jz lastCarry                   #...skacz do przeniesienia

  sub $1, %edi                   #Jeśli cmp != 0 to przejdzie tutaj i odejmie od licznika 1
  jmp addAlgo                    #Przeskocz na początek pętli


lastCarry:

  popf                           #Ściągnij flagę przeniesienia ze stosu

  xor %eax, %eax
  xor %ebx, %ebx                 #Wyczyść rejestry 2 wersja.

  adc %eax, %ebx                 #Dodaj Z UWZGLĘDNIENIEM FLAGI CF
  
  push %ebx                      #Wynik dodaj na stos 
  
  jmp end

  end:
  push $printer                 #dodaj na stos format wyświetlania danych 
  call printf                   #wywołaj funkcję printf do wyświetlenia wyników



exit:
  mov $SYSEXIT, %eax
  mov $EXIT_SUCCESS, %ebx
  int $SYSCALL