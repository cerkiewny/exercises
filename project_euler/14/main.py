maxim = 0
res = 0 
def calc(num):
    res = 0
    while(num !=1):
        if(num%2 == 0):
            num = num / 2
        else:
            num = 3*num + 1
        res+=1
    return res


for i in range(0, 1000000):
    if(i%1000 == 0):
        print(i)
    cur = 1000000 - i
    curlen = calc(cur)
    if (curlen > maxim):
        maxim = curlen
        res = cur

print res
print maxim
