import os
from pprint import pprint

# Using readlines()
f = open(os.path.join(os.getcwd(), '8.in'), 'r')
lines = f.readlines()

maze = []

for line in lines:
    maze.append([int(i) for i in list(line.strip())])

R = len(maze)
C = len(maze[0])

# print(R,C)

ans = 0
# Check for all in the middle
for r in range(1,R-1):
    for c in range(1,C-1):
        curans = 1
        
        # print(r,c,end=" ")
        # down
        ts = 0
        for rr in range(r+1,R):
            ts+=1
            if maze[rr][c]>=maze[r][c]:
                break
            
        curans *= ts
        # print(ts,end=" ")

        # up
        ts = 0
        for rr in range(r-1,-1,-1):
            ts+=1
            if maze[rr][c]>=maze[r][c]:
                break
            
        curans *= ts
        # print(ts,end=" ")

        # right
        ts = 0
        for cc in range(c+1,C):
            ts+=1
            if maze[r][cc]>=maze[r][c]:
                break
            
        curans *= ts
        # print(ts,end=" ")

        # left
        ts = 0
        prev=-1
        for cc in range(c-1,-1,-1):
            ts+=1
            if maze[r][cc]>=maze[r][c]:
                break

        curans *= ts
        # print(ts,end=" ")
        
        ans=max(ans,curans)
        # print(curans)

print(ans)
