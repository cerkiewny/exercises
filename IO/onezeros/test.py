import random
import subprocess
from subprocess import PIPE
from os import *

proc = subprocess.Popen('./a.out', stdin=PIPE, stdout=PIPE)
proc.stdin.write(str(20000) + '\n')

for i in range(1,20000):
    if(i % 100 == 0):
        print i
    a = random.random()
    proc.stdin.write(str(i) + '\n')
    res = proc.stdout.readline()
    if (res == "BRAK\n"):
        print "FAIL"
        print i
        continue
    res = int(res)
    if (res % i != 0):
        print "FAIL"
        print i

