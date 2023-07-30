import sys
import random

tc = 20
posMin = 0
posMax = 10**9
nMin = 0 
nMax = 100000

with open('aggrcow.out', 'w') as sys.stdout: 
    print(tc)
    while tc:
        tc -= 1
        n = random.randint(nMin, nMax)
        c = random.randint(nMin, n)

        print(n,c) 
        
        coords = random.sample(range(posMin, posMax), n)
        for i in coords:
            print(i)

