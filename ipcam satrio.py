import numpy as np
#import argparse
import cv2
import imutils

# construct the argument parse and parse the arguments
#ap = argparse.ArgumentParser()
#ap.add_argument("-i", "--image", help = "path to the image")
#args = vars(ap.parse_args())

cap = cv2.VideoCapture("http://10.112.1.67:8080/video")

# define the list of boundaries
# BGR
# boundaries = [
#     ([17, 15, 100], [50, 56, 200]),
#     ([86, 31, 4], [220, 88, 50]),
#     ([25, 146, 190], [62, 174, 250]),
#     ([103, 86, 65], [145, 133, 128])
# ]

# green = [([33,80,40], [102,255,255])]

# orange = [([50, 100, 255],[0, 30, 110])]

def nothing(x):
    pass
# Creating a window for later use
cv2.namedWindow('result')

# Starting with 100's to prevent error while masking
h,s,v = 100,100,100

# Creating track bar
cv2.createTrackbar('h', 'result',0,179,nothing)
cv2.createTrackbar('s', 'result',0,255,nothing)
cv2.createTrackbar('v', 'result',0,255,nothing)

while(True):
    # get info from track bar and appy to result
    h = cv2.getTrackbarPos('h','result')
    s = cv2.getTrackbarPos('s','result')
    v = cv2.getTrackbarPos('v','result')

    ret, frame = cap.read()
    frame = cv2.resize(frame, (0,0), fx=0.5, fy=0.5)
    #cv2.imshow('frame',frame)
    #image = frame

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

    #cv2.imshow("images", dilation)
    
    #cv2.imshow("images", np.hstack([frame, frame_threshed]))
    #cv2.imwrite('output2.jpg', frame_threshed)

#     # loop over the boundaries
#     for (lower, upper) in orange:
#         # create NumPy arrays from the boundaries
#         lower = np.array(lower, dtype = "uint8")
#         upper = np.array(upper, dtype = "uint8")
     
#         # find the colors within the specified boundaries and apply
#         # the mask
#         mask = cv2.inRange(frame, lower, upper)
#         output = cv2.bitwise_and(frame, frame, mask = mask)
     
#         # show the images
#         cv2.imshow("images", np.hstack([frame, output]))
# #        cv2.waitKey(0)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()