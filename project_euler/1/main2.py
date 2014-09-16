from math import *


def sumN(a, n, d):
    return (n * ( 2 * a + ( n - 1 ) * d )) / 2

sum3 = sumN(3, floor(1000 / 3), 3)
sum5 = sumN(5, floor(1000 / 5), 5)
sum15 = sumN(15, floor(1000 / 15), 15)

print sum3 + sum5 - sum15

