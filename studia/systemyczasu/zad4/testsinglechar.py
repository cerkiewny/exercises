import serial
import time
serout = serial.Serial('/dev/ptyp3', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None)  # open first serial port
serin = serial.Serial('/dev/ttyp3', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None)  # open first serial port
total = 0
for i in range(1, 1000000):
    start = time.time()
    serin.write('a') 
    end = time.time()
    total += end - start
    serout.read(1)
print total
serin.close() 
serout.close()
