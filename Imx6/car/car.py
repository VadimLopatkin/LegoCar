import cv
import numpy as np
import serial

#cv.NamedWindow("camera", 1)
capture = cv.CaptureFromCAM(3)
ser = serial.Serial("/dev/ttyUSB0")
ser.baudrate = 115200
ser.write("f");
ser.write("s");

#img = cv2.imread('testimages/4.jpg')
frame = cv.QueryFrame(capture)
#cv.ShowImage("camera", frame)

length = frame.width
mid = [round(length/2-0.5),round(length/2+0.5)]

while True:
	leftCount = 0
	rightCount = 0
	frame = cv.QueryFrame(capture)
	#cv.ShowImage("camera", frame)
	k = cv.WaitKey(10);
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
	print "left: " + str(leftCount) + ", right: " + str(rightCount)
	div = leftCount - rightCount
	if abs(div) < (leftCount + rightCount)/1.8:
		print "center"
		ser.write("s");
	elif div < 0:
		print "turn right"
		ser.write("f")
		ser.write("r");
	else:
		print "turn left"
		ser.write("l");
