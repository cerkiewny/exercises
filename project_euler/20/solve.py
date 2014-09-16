
a = 1
for i in range(1,100):
    a = a * i

res = 0
while a > 0:
    res = res + (a % 10)
    a = a / 10
print res
