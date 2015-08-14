
import serial
import time

serout  = serial.Serial('/dev/ptyp3', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None)  # open first serial port

while True:
    serout.read(1)

def at_exit():
    serout.close() 

import atexit
atexit.register(at_exit)

