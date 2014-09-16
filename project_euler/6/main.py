res = 0
sume = 0

for i in range(1,101):
    sume += i

for i in range(1,101):
    res += (sume - i) * i

print(res)
