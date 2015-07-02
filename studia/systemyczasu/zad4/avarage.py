import sys
for arg in sys.argv[1:]:
    i = 0
    f = open(arg, 'r')
    suma = 0
    for line in f.readlines():
        i += 1
        suma += float(line)
    if i != 0:
        print (suma / i)
