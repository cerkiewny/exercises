#! /usr/bin/env python
#################################################################################
#     Copyright           :     2016 Ultrahaptics
#################################################################################
import math
ret = 0
sums = [0]
for i in range(1, 10000):
    suma = 0
    for a in range (1, i):
        if i % a == 0:
            suma += a
    sums.append(suma)
    if suma < i and sums[suma] == i:
        ret += suma
        print(suma)
        print(sums[suma])
        if suma != sums[suma]:
            ret += sums[suma]
print (ret)


