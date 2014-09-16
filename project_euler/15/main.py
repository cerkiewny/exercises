poss = []
rang = 21 
for i in range(0,rang):
    a = []
    poss.append(a)
    for j in range(0,rang):
        b = []
        poss[i].append(b)
        poss[i][j] = 0

poss[0][0] = 1

for i in range(0,rang):
    for j in range(0,rang):
        if(i < rang-1):
            poss[i+1][j] +=  poss[i][j]
        if(j < rang-1):
            poss[i][j+1] +=  poss[i][j]


print (poss[rang-1][rang-1])
