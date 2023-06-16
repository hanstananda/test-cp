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
        self.bag_mapping = list()

    def map(self, bag):
        if bag not in self.bag_ids:
            self.bag_mapping.append(bag) 
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
adjList = list() # contain node linking to it and how many of the multiplier
for i in range(bag_count):
    adjList.append(list())

for rule in rules:
    source_bag = rule[0]
    source_id = bm.get(source_bag)
    for dest_bag_info in rule[1]:
        dest_id = bm.get(dest_bag_info[1])
        # create a link from parent to child 
        adjList[source_id].append((dest_id, dest_bag_info[0]))

# print(bm.bag_ids)
# print(adjList)

from collections import deque
q = deque()
q.append((bm.gold_idx, 1))
ans = 0

while (len(q)):
    cur_bag_info = q.popleft()
    cur_bag = cur_bag_info[0]
    cur_bag_cnt = cur_bag_info[1]
    # print(f"adding {cur_bag_cnt} from {bm.bag_mapping[cur_bag]}[{cur_bag}]")
    ans += cur_bag_cnt # add current count of bags 
    for dest_bag_info in adjList[cur_bag]:
        dest_bag = dest_bag_info[0]
        dest_bag_cnt = dest_bag_info[1]
        # print(f"going to traverse {bm.bag_mapping[dest_bag]} with amount of {dest_bag_cnt} ({dest_bag_cnt * cur_bag_cnt} total)")
        q.append((dest_bag, dest_bag_cnt* cur_bag_cnt)) # propagate further, multiply by current bags

print(ans-1) # number of reachable nodes, excluding the shiny gold itself 