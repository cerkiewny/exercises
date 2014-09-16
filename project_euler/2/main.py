res = 0
a = 1
b = 2
temp = 0

while(b < 4000000):
    if(b % 2 == 0):
        res += b
    temp = a + b
    a = b
    b = temp

print(res)

