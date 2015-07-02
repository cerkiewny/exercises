import sys
for arg in sys.argv[1:]:
    i = 0
    f = open(arg, 'r')
    suma = 0
    minim = 100.0
    maxim = 0.0
    lines = f.readlines()
    for line in lines:
        i += 1
        suma += float(line)
        if float(line) > maxim:
            maxim = float(line)
        if float(line) < minim:
            minim = float(line)
    step = (maxim - minim) / 100.0

    for line in lines:
        print int((float(line) - minim) / step)

    if i != 0:
        print (suma / i)
        print minim
        print maxim
