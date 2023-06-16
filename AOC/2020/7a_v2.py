import os
from pprint import pprint

# Using readlines()
f = open(os.path.join(os.getcwd(), '7.in'), 'r')
lines = f.readlines()

ans = 0

# map bag name to a number for easier processing
class BagMapping:
    def __init__(self):
        self.idx = 0
        self.gold_idx = -1
        self.bag_ids = dict()

    def map(self, bag):
        if bag not in self.bag_ids: 
            self.bag_ids[bag] = self.idx
            if bag == "shinygold":
                self.gold_idx = self.idx
            self.idx+=1

    def get(self, bag):
        return self.bag_ids[bag]
    
    def size(self):
        return self.idx
    

bm = BagMapping()
rules = []
for line in lines:
    # parsing, can consider using regex also
    rule = line.split(" ")
    # s_1 s_2 bags contain (no other bags)/(num d_1 d_2 bags(./,...) )
    source_bag = rule[0] + rule[1]
    bm.map(source_bag)
    if rule[4] == "no":
        continue # contain no bags, no need to care
    dest_bags = []
    for i in range(4,len(rule),4):
        num = rule[i]
        dest_bag = rule[i+1] + rule[i+2]
        bm.map(dest_bag)
        dest_bags.append((int(num),dest_bag))
    
    # print(source_bag, dest_bags)

    rules.append((source_bag, dest_bags))

# pprint(rules)

# Create mapping for the relationship
bag_count = len(bm.bag_ids)
adjList = list()
for i in range(bag_count):
    adjList.append(list())

for rule in rules:
    source_bag = rule[0]
    source_id = bm.get(source_bag)
    for dest_bag_info in rule[1]:
        dest_id = bm.get(dest_bag_info[1])
        # create a link from child to parent 
        adjList[dest_id].append(source_id)

# print(bm.bag_ids)
# print(adjList)

visited = [False] * bag_count
from collections import deque
q = deque()
q.append(bm.gold_idx)

while (len(q)):
    cur_bag = q.popleft()
    if not visited[cur_bag]:
        # print(f"visiting {cur_bag})")
        visited[cur_bag] = True
        for dest_bag in adjList[cur_bag]:
            q.append(dest_bag)

ans = visited.count(True)
print(ans-1) # number of reachable nodes, excluding the shiny gold itself 