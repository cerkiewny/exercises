
res = 0
primes  = [ True for x in range( 10000 ) ]

def ispermut(a, b):
    returnvalue = False
    if len(a) == len(b):
      returnvalue = (sorted(a) == sorted(b))
    return returnvalue

for i in range (2, 9999):
    a = i + i
    while(a < 10000):
        primes[a] = False
        a = a + i

for i in range(1000,9999):
    for j in range(2, 3334):
        a = i
        b = i +j
        c = i + j + j
        if(c < 10000):
            if(primes[a] and primes[b] and primes[c]):
                if(ispermut(str(a),str(b)) and ispermut(str(b),str(c))):
                    print str(a) + str(b) + str(c)
