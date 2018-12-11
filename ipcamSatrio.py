import numpy as np
#import argparse
import cv2
import imutils
import serial

# construct the argument parse and parse the arguments

# cap = cv2.VideoCapture("http://10.112.1.128:8080/video")
cap = cv2.VideoCapture("http://192.168.43.1:8080/video")

# ser1 = serial.Serial('COM4', 9600)

def nothing(x):
    pass

# Creating a window for later use
cv2.namedWindow('result')

# Starting with 100's to prevent error while masking
# h,s,v = 100,100,100

# Creating track bar
# cv2.createTrackbar('h', 'result',0,179,nothing)
# cv2.createTrackbar('s', 'result',0,255,nothing)
# cv2.createTrackbar('v', 'result',0,255,nothing)

while(True):
    # get info from track bar and appy to result
    # h = cv2.getTrackbarPos('h','result')
    # s = cv2.getTrackbarPos('s','result')
    # v = cv2.getTrackbarPos('v','result')
    h = 0
    s = 100
    v = 100
    ret, frame = cap.read()
    frame = cv2.resize(frame, (0,0), fx=0.5, fy=0.5)
    
    height, width, channel = frame.shape

    ORANGE_MIN = np.array([h, s, v],np.uint8)
    ORANGE_MAX = np.array([15, 255, 255],np.uint8)

    hsv_img = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

    frame_threshed = cv2.inRange(hsv_img, ORANGE_MIN, ORANGE_MAX)
    kernel = np.ones((10,10),np.uint8)
    opening = cv2.morphologyEx(frame_threshed, cv2.MORPH_OPEN, kernel)
    kernel = np.ones((20,20),np.uint8)
    dilation = cv2.dilate(opening,kernel,iterations = 1)

    # find contours in the thresholded image
    cnts = cv2.findContours(dilation.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cnts = cnts[0] if imutils.is_cv2() else cnts[1]
    
    # Boundary for moving
    boundLeft = int(width * 0.40)
    boundRight = int(width * 0.60)

    for c in cnts:

        con = max(cnts, key = cv2.contourArea)
    	# compute the center of the contour
        M = cv2.moments(con)
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])

        # draw the contour and center of the shape on the image
        cv2.drawContours(frame, [c], -1, (0, 255, 0), 2)
        
        #find the biggest area
        x,y,w,h = cv2.boundingRect(con)
        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),2)

        (x,y),radius = cv2.minEnclosingCircle(con)
        center = (int(x),int(y))
        radius = int(radius)
    
        cv2.circle(frame,center,radius,(255,255,0),2)
        
        cv2.circle(frame, (cX, cY), 7, (255, 255, 255), -1)

        cv2.line(frame,(int(x),int(y-h/2)),(int(x),int(y+h/2)),(255,0,0),5)
        
        cv2.line(frame,(boundLeft,0),(boundLeft,height),(255,0,0),3)
        cv2.line(frame,(boundRight,0),(boundRight,height),(255,0,0),3)

        if cX > boundRight:
        	# Geser robot ke kanan
            # ser1.write('1'.encode()) 
            print ("Kanan")
        elif cX < boundLeft:
            # ser1.write('0'.encode())
            print("Kiri")
        	# Geser robot ke kiri
        else:
            # ser1.write('2'.encode())
            print("Ya")

    # show the image
    cv2.imshow("Image", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
