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
for i in range(0,len(numbers),pixel_num_split):
    layers.append(numbers[i:i+pixel_num_split])

final_layer = layers[0]

for layer in layers:
    for idx, pixel in enumerate(layer):
        if final_layer[idx] == 2: # still transparent
            final_layer[idx] = pixel

for y in range(pixel_length):
    for x in range(pixel_width):
        if final_layer[y*pixel_width+x]==0: # Change zeros and ones to spaces and #'s so it becomes more legible
            out_pix=' '
        else:
            out_pix='#'
        print(out_pix, end=" ")
    print()

