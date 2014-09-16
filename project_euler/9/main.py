import math

for i in range(0, 997):
    for j in range(i, 1000 - i):
        k = 1000 - i - j
        if  ( k*k == j*j + i*i):
            print("solution")
            print(i)
            print(j)
            print(k)
            print(i*j*k)
