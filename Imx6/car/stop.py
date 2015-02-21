import serial

ser = serial.Serial("/dev/ttyUSB0")
ser.boudrate = 115200
ser.write("h")
ser.write("h")
ser.close()
