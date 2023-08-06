import sys
import random

tc = 20
nMin = 1
nMax = 100
packetMin = 1
packetMax = 3000
overrideN = { 3:1, 2:100 , 10:100, 14:100 , 17:50 }


with open('10261_tc.in', 'w') as sys.stdout: 
    print(tc)
    print()
    for i in range(tc):
        n = random.randint(nMin, nMax)
        if i in overrideN:
            n = overrideN[i]
        print(n) 
        max_badwidth_size = n * 1000 * 2
        
        allowOver = bool(random.getrandbits(1))
        leftover = max_badwidth_size
        while leftover > 0 or allowOver:
            if leftover <= 0 and allowOver: 
                # gacha whether to continue generating
                allowOver = bool(random.getrandbits(1))
            
            p = random.randint(packetMin, packetMax)
            print(p)
            leftover -= p
        
        # Last line is 0 then empty line
        print(0)
        print()
