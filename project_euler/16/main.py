import math

val = 1
for i in range(0,1000):
    val *= 2
print(val)
sume = 0

while(val > 0):
    sume += val%10
    val = (val - (val % 10)) / 10

print (sume)
