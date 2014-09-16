import math

def countdiv(num):
    i = 2
    res = 1
    cur = 1
    temp = 1
    while( i <= num):
        if(num%i == 0 ):
            num = num / i
            cur+=1
            continue
        res = res * cur + (cur - 1)
        i+= 1
        cur = 1
    return res

i = 1
sume = 0
div = 0
while (div <= 500):
    sume += i
    i+=1
    div = countdiv(sume)
    print(div)
print(sume) 
