import os
from pprint import pprint

# Using readlines()
f = open(os.path.join(os.getcwd(), '7_sample.in'), 'r')
lines = f.readlines()


class UnionFind:
    def __init__(self, size):
        self.parent = list(range(size))

    def findSet(self,i) -> int:
        if self.parent[i] == i:
            return i
        else:
            self.parent[i] = self.findSet(self.parent[i])
            return self.parent[i]

    def isSameSet(self, i, j) -> bool:
        return self.findSet(i) == self.findSet(j)
    
    def unionSet(self, i, j):
        if not self.isSameSet(i,j):
            x = self.findSet(i)
            y = self.findSet(j)
            self.parent[y] = x
    
    def debug(self):
        print(self.parent)
        

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
        dest_bags.append((num,dest_bag))
    
    # print(source_bag, dest_bags)

    rules.append((source_bag, dest_bags))

pprint(rules)

# Create UF and run union for all relationship 
UF = UnionFind(bm.size()+1)
for rule in rules:
    source_bag = rule[0]
    source_id = bm.get(source_bag)
    for dest_bag_info in rule[1]:
        dest_id = bm.get(dest_bag_info[1])
        UF.unionSet(source_id, dest_id)
        UF.debug()
        print(f"union {source_bag} with {dest_bag_info}")

for i in range(bm.size()):
    gold_idx = bm.gold_idx
    if UnionFind.isSameSet(i,gold_idx):
        ans+=1

print(ans)