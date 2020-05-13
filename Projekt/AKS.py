import math
import multiprocessing
import os
import sys
import warnings
from sys import argv

def Aks(args):
        #print()
        args = int(args)
        if(firstStep(args) is True):   
                r = secondStep(args)
                if (thirdStep(args,r) is True):       #Trzeci warunek nie jest równy False
                        if (fourthStep(args, r) is True):
                                print('P: Liczba jest pierwsza')
                        else:
                                if(fifthStep(args,r) is True):
                                    print('P: Liczba jest pierwsza')
                                else:
                                    print('P: Liczba nie jest pierwsza')
                else:
                        print('P: Liczba nie jest pierwsza')
        else:
                print('P: Liczba nie jest pierwsza')
        


def firstStep(n):
    for b in range(2,int(math.floor((math.log2(n)+1))), 1):
            a = n**(1/b)
            if math.floor(a) == a:
                    return False
    return True


#Szuaknie takich liczb które n^k %r == 1, n,r(liczby względnie pierwsze, np.
#Niech n = 11, wtedy r = 13, a najbliższe k, które da wynik większy niż
# log2(n)^2 to k=17. Wynik = 17.

def secondStep(n):              
        minK = math.floor(math.log2(n)**2)
        nextr = True
        r = 1
        while nextr is True:
            r += 1
            nextr = False
            k = 0
            while k <= minK and nextr is False:
                k = k+1
                if pow(n, k, r) in (0, 1):
                    nextr = True
        return r


def thirdStep(n, r):
    for a in range(1, r+1, 1):
            if((1 < math.gcd(a,n)) and (math.gcd(a,n) <n)):
                    return False
    return True


def fourthStep(n, r):
    if(n <= r):
            return True
    else:
            return False

 
def fifthStep(n, r):
    phiN = eulerFunction(r)
    maxRange = math.floor(math.sqrt(phiN)*math.log2(n))
    pythonManager = multiprocessing.Manager()
    sharedDictionary = pythonManager.dict()
    
    processes = []

    for a in range(0, maxRange, 1):
        proces = multiprocessing.Process(target=handlePolynomials, args=(n,a, a+1, sharedDictionary))
        proces.start()
        processes.append(proces)
    for Pn in processes:
        Pn.join()
        
    if False not in sharedDictionary.values():
            return True
    else:
            return False

#Funkcja tworząca wielomiany zgodnie ze wzórem skróconego mnożenia
#(a+b)^n. Wykorzystany symbol newtona (n po k).
def handlePolynomials(number, n, k, sharedDictionary):
    power = n/(k-n)
    if n == 0:
        n = 1
    for a in range(n,k,1):
        b = power(a,n,n)
        if ((b-a) != 0):
            sharedDictionary[x] = False
            return False
    sharedDictionary[x] = True
    return True


#Funckcja obliczajaca funkcje eulera, tzw. Totient.
def eulerFunction(n):
    result = 0
    for i in range(1, n + 1, 1):
            if(math.gcd(i, n) == 1):
                    result += 1
    return result

def trivial(n):
        if n == 2:
            return True
        for i in range(2, math.floor(math.sqrt(n)) + 1):
            if n % i == 0:
                return False

        return True

def main():
        Aks(input('Podaj liczbe: '))


