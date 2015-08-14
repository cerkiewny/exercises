import serial
import time
serin = serial.Serial('/dev/ttyp3', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None)  # open first serial port
total = 0
end = False

start = time.time()
for i in range(1, 500000):
    serin.write(b'\x01')
end = time.time()
print (end - start) / 500000
time.sleep(0.5)
serin.close()
