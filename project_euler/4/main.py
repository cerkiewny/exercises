

def is_pali(number):
    temp1 = number
    temp2 = 0
    while(temp1):
        temp2 *= 10
        temp2 += temp1 % 10
        temp1 /= 10;
    return temp2 == number

res = 0

for a in range(100,999):
    for b in range(a + 1,999):
        if(is_pali(a*b) and a*b > res):
            res = a*b

print(res)
