import random

def fermat(args):
    i=0
    repeats=20
    number = int(args)
    while i<repeats:
        a = random.randint(1,number-1)
        if pow(a,(number-1),number) != 1:
            return False
            #liczba nie jest pierwsza
        i = i+1
    #print('Liczba jest pierwsza.')
    return True
