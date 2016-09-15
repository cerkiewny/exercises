#! /usr/bin/env python
#################################################################################
#     Copyright           :     2016 Ultrahaptics
#################################################################################

import math

canbe = [False]
abbund = []
ret = 0
for i in range(1,28124):
    canbe.append(False);
    suma = 0
    if(i % 100 == 0):
        print(i)
    for j in range (1, i / 2 + 1):
        if( i % j == 0):
            suma += j
    if(suma > i):
        abbund.append(i)

for a in abbund:
    for b in abbund:
        if (a + b <= 28123):
             canbe[a+b] = True
        else:
            break

for a in range(1, len(canbe)):
    if (not canbe[a]):
        ret += a
print (ret)
