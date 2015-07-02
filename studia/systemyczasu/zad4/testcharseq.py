import serial
import time
serout = serial.Serial('/dev/ptyp3', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None)  # open first serial port
serin = serial.Serial('/dev/ttyp3', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None)  # open first serial port
total = 0
for i in range(1, 10000):
    start = time.time()
    serin.write(b'\x01')
    end = time.time()
    serout.read(1)
    print (end - start) / 8
    start = time.time()
    serin.write(b'\x03')
    end = time.time()
    serout.read(1)
    print (end - start) / 8
    start = time.time()
    serin.write(b'\x00')
    end = time.time()
    serout.read(1)
    print (end - start) / 8
    start = time.time()
    serin.write(b'\x00')
    end = time.time()
    serout.read(1)
    print (end - start) / 8
    start = time.time()
    serin.write(b'\x00')
    end = time.time()
    serout.read(1)
    print (end - start) / 8
    start = time.time()
    serin.write(b'\x02')
    end = time.time()
    serout.read(1)
    print (end - start) / 8
    start = time.time()
    serin.write(b'\xC4')
    end = time.time()
    serout.read(1)
    print (end - start) / 8
    start = time.time()
    serin.write(b'\x0B')
    end = time.time()
    serout.read(1)
    print (end - start) / 8
serin.close() 
serout.close()
