import time
import cv2 as cv


video = cv.VideoCapture(0)
a = 0

while True:
    a+=1
    check, frame = video.read()
    #cv.imshow('Normal Image', frame)

    mirror = cv.flip(frame, 1)
    # cv.imshow('Mirror Image', mirror)

    if cv.waitKey(1) == 27:
        break

    gray = cv.cvtColor(mirror, cv.COLOR_BGR2GRAY)
    ret, thresh = cv.threshold(gray, 150, 255, cv.THRESH_BINARY)
    contours, hierarchy = cv.findContours(thresh, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    cv.drawContours(gray, contours, -1, (0, 255, 0), 3)

    cv.imshow('Image with contours', gray)


    start = time.time()
    if len(contours) > 0:
        c = max(contours, key=cv.contourArea)
        end = time.time()
        print( str(round((end - start)*1000, 2)) + "ms")



video.release()
cv.destroyAllWindows()