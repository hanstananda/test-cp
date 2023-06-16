import os
from pprint import pprint

# Using readlines()
# f = open(os.path.join(os.getcwd(), '8_sample.in'), 'r')
f = open(os.path.join(os.getcwd(), '8.in'), 'r')
lines = f.readlines()
numbers = list(map(int,list(lines[0].strip())))

# for sample 
# pixel_width = 3
# pixel_length = 2

pixel_width = 25
pixel_length = 6
pixel_num_split = pixel_width * pixel_length 

layers = []
min_layer = []
min_zeros = pixel_num_split # set as max val for now
for i in range(0,len(numbers),pixel_num_split):
    layers.append(numbers[i:i+pixel_num_split])

for layer in layers:
    zeros = layer.count(0)
    if zeros < min_zeros:
        min_layer = layer
        min_zeros = zeros

# print(min_layer)
ans = min_layer.count(1) * min_layer.count(2)

print(ans)

