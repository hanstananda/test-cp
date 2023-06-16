import os
from pprint import pprint

# Using readlines()
f = open(os.path.join(os.getcwd(), '8.in'), 'r')
lines = f.readlines()

maze = []
visible = []

for line in lines:
    maze.append([int(i) for i in list(line.strip())])
    visible.append([0]*len(maze[-1]))

# pprint(maze)
# pprint(visible)
R = len(maze)
C = len(maze[0])

print(R,C)

# Check left to right for each row
for r in range(R):
    prev=-1
    for c in range(C):
        if maze[r][c]>prev:
            visible[r][c]=1
            prev = maze[r][c]

# pprint(visible)

# Check right to left for each row
for r in range(R):
    prev=-1
    for c in range(C-1,-1,-1):
        if maze[r][c]>prev:
            visible[r][c]=1
            prev = maze[r][c]

# pprint(visible)

# Check top to bottom for each column
for c in range(C):
    prev=-1
    for r in range(R):
        if maze[r][c]>prev:
            visible[r][c]=1
            prev = maze[r][c]

# pprint(visible)

# Check bottom to top for each column
for c in range(C):
    prev=-1
    for r in range(R-1,-1,-1):
        if maze[r][c]>prev:
            visible[r][c]=1
            prev = maze[r][c]

# pprint(visible)
print(sum([sum(i) for i in visible]))