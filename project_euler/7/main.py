primes = [None] * 1000001

counter = 0
current = 2

while(counter!=10001):
    if(primes[current]!= None):
        current+=1
        continue
    counter+=1
    j = current
    j += current
    while(j < 1000001):
        primes[j] = 1
        j += current
    current+=1
print(current-1)
