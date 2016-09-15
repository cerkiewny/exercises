#! /usr/bin/env python
#################################################################################
#     Copyright           :     2016 Ultrahaptics
#################################################################################

f = open('names', 'r')
names = f.readline()

names = names.split(',')
order = 0
ret = 0
for name in sorted(names, key=str.lower):
    order += 1
    sums = 0
    for c in name:
        if (c.isalnum()):
            sums += ord(c) - ord('A') + 1
            print(c)
    ret += sums * order
    print (sums)
    print (order)
print ret

