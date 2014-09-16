


def numtostring(num):
    if(num == 0):
        return "" 
    elif(num == 1):
        return "one"
    elif(num == 2):
        return "two"
    elif(num == 3):
        return "three"
    elif(num == 4):
        return "four"
    elif(num == 5):
        return "five"
    elif(num == 6):
        return "six"
    elif(num == 7):
        return "seven"
    elif(num == 8):
        return "eight"
    elif(num == 9):
        return "nine"
    elif(num == 10):
        return "ten"
    elif(num == 11):
        return "eleven"
    elif(num == 12):
        return "twelve"
    elif(num == 13):
        return "thirteen"
    elif(num == 15):
        return "fifteen"
    elif(num == 18):
        return "eighteen"
    elif(num < 20):
        return(numtostring(num - 10) + "teen")
    elif(num < 30):
        return "twenty" + numtostring(num - 20)
    elif(num < 40):
        return "thirty" + numtostring(num - 30)
    elif(num == 80):
        return "eighty"
    elif(num == 100):
        return "onehundred"
    elif(num < 100):
        return numtostring((num - (num % 10))/10) + "ty" + numtostring(num%10)
    elif(num < 200):
        return numtostring((num - num % 100)/ 100) + "hundred" + numtostring(num % 100)
    elif(num < 1000):
        return numtostring((num - num % 100)/ 100) + "hundredand" + numtostring(num % 100)
    if(num == 1000):
        return "thousend"
ret = 0
for i in range( 1, 1001):
    print(numtostring(i))
    print(len(numtostring(i)))
    ret += len(numtostring(i))

print(ret)
