from MillerRabin import *
import random

def checkSection(number):
    sections = [0,2047,1373653,9080191,25326001,3215031751,4759123141,1122004669633,2152302898747,3474749660383,341550071728321,3825123056546413051,18446744073709551616]
    if number == sections[0]:
        return []
    elif(number > sections[0] and number < sections[1]):
        return [2]
    elif(number >= sections[1] and number < sections[2]):
        return [2,3]
    elif(number >= sections[2] and number < sections[3]):
        return [31,73]
    elif(number >= sections[3] and number < sections[4]):
        return [2,3,5]
    elif(number >= sections[4] and number < sections[5]):
        return [2,3,5,7]
    elif(number >= sections[5] and number < sections[6]):
        return [2,7,61]
    elif(number >= sections[6] and number < sections[7]):
        return [2,13,23,1662803]
    elif(number >= sections[7] and number < sections[8]):
        return [2,3,5,7,11]
    elif(number >= sections[8] and number < sections[9]):
        return [2,3,5,7,11,13]
    elif(number >= sections[9] and number < sections[10]):
        return [2,3,5,7,11,13,17]
    elif(number >= sections[10] and number < sections[11]):
        return [2,3,5,7,11,13,17,19,23]
    elif(number >= sections[11] and number < sections[12]):
        return [2,3,5,7,11,13,17,19,23,29,31,37]
    else:
        returnValues=[]
        for i in range(0,20,1):
            returnValues.append(random.randint(1,10000))
        return returnValues
    

def checkPrime(n,s,d,k,array):

    for i in range(0,k,1):
        
        a = array[i]
        
        if(FME(a,d,n) != 1):
            
            for r in range(0,s,1):
                temporary = (2**r)*d
                
                if(FME(a,temporary,n) != (n-1)):
                    if( r == (s-1)):
                        return False
                else:
                    break
    
    return True


def MillerRabinDeterministic(args):
    n = int(args)
    s = maxPower(n)
    d = n//(2**s)
    k = 10
    numbers = checkSection(n)
    result = checkPrime(n,s,d,len(numbers),numbers)
    if(result == True):
        print('Liczba jest pierwsza.')
    else:
        print('Liczba nie jest pierwsza.')
