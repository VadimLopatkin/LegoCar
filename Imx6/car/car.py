import cv
import numpy as np
import serial

#cv.NamedWindow("camera", 1)
capture = cv.CaptureFromCAM(3)
ser = serial.Serial("/dev/ttyUSB1")
ser.baudrate = 115200
direction = "s"
ser.write("b");
ser.write("b");
ser.write(direction);

#img = cv2.imread('testimages/4.jpg')
frame = cv.QueryFrame(capture)
#cv.ShowImage("camera", frame)

length = frame.width
mid = [round(length/2-0.5),round(length/2+0.5)]
loopCounter = 0

while True:
	loopCounter = loopCounter + 1
	leftCount = 0
	rightCount = 0
	frame = cv.QueryFrame(capture)
	#cv.ShowImage("camera", frame)
	k = cv.WaitKey(10);
	if(loopCounter > 20):
		ser.write(direction)
		print "send direction: ", direction
		ser.write("b")
		print "send backwards"
		loopCounter = 0
	for j in range(0,frame.height,4):
		for i in range(0,length,3):
			if sum(cv.Get2D(frame, j, i)) < 300:
				#img[j][i] = [255, 0, 0]
				#if i == mid[0] or i == mid[1]:
					#img[j][i] = [0, 0, 255]
				if i > length/2:
					rightCount += 1
				else:
					leftCount += 1
	#print "left: " + str(leftCount) + ", right: " + str(rightCount)
	div = leftCount - rightCount
	if abs(div) < (leftCount + rightCount)/1.8:
		#print "center"
		if(direction != "s"):
			direction = "s"
			print direction
			ser.write(direction)
	elif div < 0:
		#print "turn right"
		if(direction != "l"):
			direction = "l"
			print "send direction: ", direction
			ser.write(direction)
	else:
		#print "turn left"
		if(direction != "r"):
			direction = "r"
			print "send direction: ", direction
			ser.write(direction)