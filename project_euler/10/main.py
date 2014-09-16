test = [None] * 2000000

res = 0

for i in range(2, 2000000):
    if test[i] != None:
        continue
    res += i
    j = i
    while(j < 2000000):
        test[j] = 1
        j+= i

print(res)
