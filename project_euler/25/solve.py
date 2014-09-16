

a = 1

for i in range(1, 1000):
    a = a * 10

b = 1
c = 1
res = 2
while ( a > b):
    res = res + 1
    f = b + c
    c = b
    b = f

print res
