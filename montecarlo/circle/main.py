import random

inside = 0
outside = 0
for i in range(0, 10000000):
    randx = 1 - random.random() * 2
    randy = 1 - random.random() * 2
    if(randx*randx + randy*randy > 1):
        outside+=1
    else:
        inside +=1

print "pi = " + str(float(inside) / (outside+inside)*4)
