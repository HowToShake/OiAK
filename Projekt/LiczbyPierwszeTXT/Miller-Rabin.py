import random
import time
#import keyboard
m = 100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000081
def generateOddNumber():
    return (2*random.randint(1,m))+1


#n = generateOddNumber()
#n = int(input("Podaj liczbe: "))
def maxPower(number):
    maximumPower = 0

    while True:
        if((number-1) % 2** maximumPower == 0):
            maximumPower += 1
            continue
        else:
            break
        
    return maximumPower-1


def FME(a, k, n):
    b = bin(k)[2:] # list of bits
    m = len(b)
    r = 1 # result
    x = a % n
 
    for i in range(m - 1, -1, -1):
        if b[i] == '1':
            r = r * x % n
 
        x **= 2
        x  %= n
    return r

#print('Liczba wylosowana: ')
#print(n)

#print('Liczba s: ')
#s = maxPower(n)
#print(s)

#print('Liczba d: ')
#d = n//(2**s)
#print(d)

k = 10 #dokladnosc testu

def checkPrime(number):
    n = number
    s = maxPower(n)
    d = n//(2**s)

    for i in range(0, k, 1):
        
        a = random.randint(2,n-1)
        
        if(FME(a,d,n) != 1):
            
            for r in range(0,s,1):
                temporary = (2**r)*d

                if(FME(a,temporary,n) != (n-1)):
                    if( r == (s-1)):
                        return False
                if(FME(a,temporary,n) == (n-1)):
                    break
    
    return True

i = 90384421
f=open("primes.txt","a+")
print('OTWARLEM?')
while True:
    #print("PETLA")
    if(checkPrime(i)== True):
        f.write(str(i)+"\n")
    i+=2

f.close()
    



