#import argparse
import numpy as np
import cv2
import imutils

cap = cv2.VideoCapture("http://10.112.1.142:8080/video")

# HSV value for the color orange
h, s, v = 0, 107, 100

while(True):
    ret, frame = cap.read()
    frame = cv2.resize(frame, (0, 0), fx=0.5, fy=0.5)

    ORANGE_MIN = np.array([h, s, v], np.uint8)
    ORANGE_MAX = np.array([15, 255, 255], np.uint8)

    hsv_img = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    frame_threshed = cv2.inRange(hsv_img, ORANGE_MIN, ORANGE_MAX)
    kernel = np.ones((10, 10), np.uint8)
    opening = cv2.morphologyEx(frame_threshed, cv2.MORPH_OPEN, kernel)

    kernel = np.ones((20, 20), np.uint8)
    dilation = cv2.dilate(opening, kernel, iterations=1)

    # find contours in the thresholded image
    cnts = cv2.findContours(
        dilation.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cnts = cnts[0] if imutils.is_cv2() else cnts[1]

    for c in cnts:
        # compute the center of the contour
        M = cv2.moments(c)
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])

        # draw the contour and center of the shape on the image
        cv2.drawContours(frame, [c], -1, (0, 255, 0), 2)
        cv2.circle(frame, (cX, cY), 7, (255, 255, 255), -1)
        # show the image
        cv2.imshow("Image", frame)

    # cv2.imshow("images", opening)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
