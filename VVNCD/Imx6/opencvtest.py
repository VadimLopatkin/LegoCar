import cv
import time

capture = cv.CaptureFromCAM(0)

# if capture:
#     img = cv.QueryFrame(capture)
#     if img is None:
#         print("Error")
#     cv.SaveImage("test1.jpg", img)
# else:
#     print("!!! Failed CreateCameraCapture: invalid parameter!")


while True:
	img = cv.QueryFrame(capture)
	print img
	time.sleep(1);