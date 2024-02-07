import cv2 as cv 
import numpy as np

img = np.zeros((100, 100, 3), np.uint8) 

#Crease a window 
cv.namedWindow("Display window", cv.WINDOW_AUTOSIZE)
radius = 20
center = (30, 30)
cv.circle(img, center, radius, (255,0,0), -1)
cv.imshow("Display window", img)
k = cv.waitKey(0) # Wait for a keystroke in the window