import cv
import numpy as np
import serial

# initialization of camera and serial port conenction
capture = cv.CaptureFromCAM(3)
ser = serial.Serial("/dev/ttyUSB1")
ser.baudrate = 115200

# s - straight; b - backwards; f - forward; l - left; r - right
direction = "s"
ser.write("b");
ser.write("b");
ser.write(direction);

frame = cv.QueryFrame(capture)

length = frame.width
mid = [round(length/2-0.5),round(length/2+0.5)]
loopCounter = 0

while True:
	loopCounter = loopCounter + 1
	leftCount = 0
	rightCount = 0
	frame = cv.QueryFrame(capture)
	k = cv.WaitKey(10);
	if(loopCounter > 20):
		# "confirm" direction from time to time in case of possible error
		ser.write(direction)
		print "send direction: ", direction
		ser.write("b")
		print "send backwards"
		loopCounter = 0
	# count black pixels in each half
	for j in range(0,frame.height,4):
		for i in range(0,length,3):
			if sum(cv.Get2D(frame, j, i)) < 300:
					rightCount += 1
				else:
					leftCount += 1
	div = leftCount - rightCount
	# go straight
	if abs(div) < (leftCount + rightCount)/1.8:
		if(direction != "s"):
			direction = "s"
			print direction
			ser.write(direction)
	# turn left
	elif div < 0:
		if(direction != "l"):
			direction = "l"
			print "send direction: ", direction
			ser.write(direction)
	# turn right
	else:
		if(direction != "r"):
			direction = "r"
			print "send direction: ", direction
			ser.write(direction)