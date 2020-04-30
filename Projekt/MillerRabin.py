import random
import time

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
    b = bin(k)[2:] #list of bits
    m = len(b)
    r = 1 #result
    x = a % n
 
    for i in range(m - 1, -1, -1):#for(int i = m-1; i>=0; i--)
        if b[i] == '1':
            r = r * x % n
            #print(r)
        x **= 2
        x  %= n
        #print(i)
    return r

#print('Liczba wylosowana: ')
#print(n)

#print('Liczba s: ')
#s = maxPower(n)
#print(s)

#print('Liczba d: ')
#d = n//(2**s)
#print(d)

#k = 10 #dokladnosc testu

def checkPrime(n,s,d,k):

    for i in range(0, k, 1):
        
        a = random.randint(2,n-1)
        
        if(FME(a,d,n) != 1):
            
            for r in range(0,s,1):
                temporary = (2**r)*d
                #print('TEMPORARY: ',temporary)
                #print('FME: ',FME(a,temporary,n))
                if(FME(a,temporary,n) != (n-1)):
                    if( r == (s-1)):
                        return False
                else:
                    break
    
    return True

#start = time.time()
#x = checkPrime()
#end = time.time()

#print('Czas trwania to :' ,end-start,'s . Czy liczba jest pierwsza?', x)
#v=input()

def MillerRabin(args):
    n = int(args)
    s = maxPower(n)
    d = n//(2**s)
    k = 10
    result = checkPrime(n,s,d,k)
    if(result == True):
        print('Liczba jest pierwsza.')
    else:
        print('Liczba nie jest pierwsza.')

def Test():
    FME(1000000000000000000000000000000000000000000000000121,1000000000000000000000000000000000000000000000000121,123235151235325215)
