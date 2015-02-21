import serial

tty=serial.Serial("/dev/ttyUSB0", 1000, 9600)
output = ''
output = '' + chr(0x08) + chr(0x11) 

tty.write(output)