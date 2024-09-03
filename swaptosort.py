n, k = map(int,input().strip().split(" "))

pairs = list(range(0,n+1))

def findSet(i):
    if pairs[i] == i:
        return i
    else:
        pairs[i]=findSet(pairs[i])
        return pairs[i]

def isSameSet(a,b):
    return findSet(a) == findSet(b)

def unionSet(a,b):
    i = findSet(a)
    j = findSet(b)
    if i != j:
        # just assume first one is longer, it's good enough
        pairs[i] = j

for i in range(k):
    ai,bi = map(int, input().strip().split(" "))
    unionSet(ai,bi)

# for i in range(1,n+1):
#     print(pairs[i], end=" ")
# print()

valid = True
for i in range(1,n//2+2):
    if not isSameSet(i,n-i+1):
        valid = False

if valid:
    print("Yes")
else:
    print("No")


"""
Test case
7 4
1 2 
2 3 
5 6 
6 7

7 5
1 2 
2 3 
5 6 
6 7
1 5
"""