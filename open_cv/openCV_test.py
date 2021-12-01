# -*- coding: utf-8 -*-
"""
Created on Fri Sep 24 12:09:23 2021
@author: Cole
"""

""" 'CAMERA TEST'
import cv2
import time
cap = cv2.VideoCapture(0)
pTime = 0
while True:
    success, img = cap.read()
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime
    cv2.putText(img, f'FPS:{int(fps)}', (20, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    cv2.imshow("Test", img)
    
    cv2.waitKey(1)
    
"""

""" 'just hand tracking'
import cv2
import mediapipe as mp
import time
cap = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
hands = mpHands.Hands(static_image_mode = False,
                       max_num_hands = 2,
                       min_detection_confidence = 0.5,
                       min_tracking_confidence = 0.5)
mpDraw = mp.solutions.drawing_utils
pTime = 0
cTime = 0
while True:
    success, img = cap.read()
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(imgRGB)
    #print(results.multi_hand_landmarks)
    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks:
            for id, lm in enumerate(handLms.landmark):
                #print(id, lm)
                h, w, c = img.shape
                cx, cy = int(lm.x *w), int(lm.y*h)
                #if id == 0:
                cv2.circle(img, (cx,cy), 3, (255, 0, 255), cv2.FILLED)
                    
            mpDraw.draw_landmarks(img, handLms, mpHands.HAND_CONNECTIONS)
    cTime = time.time()
    fps = 1/(cTime-pTime)
    pTime = cTime
    cv2.putText(img,str(int(fps)), (10,70), cv2.FONT_HERSHEY_PLAIN, 3, (255,0,255), 3)
    cv2.imshow("Image", img)
    cv2.waitKey(1)
    
""" 

import cv2
import mediapipe as mp
import time
import serial


class handDetector():
    def __init__(self, mode = False, maxHands = 2, detectionCon = 0.5, trackCon = 0.5):
        self.mode = mode
        self.maxHands = maxHands
        self.detectionCon = detectionCon
        self.trackCon = trackCon

        self.mpHands = mp.solutions.hands
        self.hands = self.mpHands.Hands(self.mode, self.maxHands, self.detectionCon, self.trackCon)
        self.mpDraw = mp.solutions.drawing_utils
        self.lmlist = []
        
    def findHands(self,img, draw = True):
        imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        self.results = self.hands.process(imgRGB)
        # print(results.multi_hand_landmarks)

        if self.results.multi_hand_landmarks:
            for handLms in self.results.multi_hand_landmarks:
                if draw:
                    self.mpDraw.draw_landmarks(img, handLms, self.mpHands.HAND_CONNECTIONS)
        return img

    def findPosition(self, img, time, handNo = 0, draw = True):

        lmlist = []
        if self.results.multi_hand_landmarks:
            myHand = self.results.multi_hand_landmarks[handNo]
            for id, lm in enumerate(myHand.landmark):
                h, w, c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                
                if id == 2 or id == 5:
                   xs, xy = int(lm.x * w), int(lm.y * h)
                if id == 4:
                    lmlist.append([2, (cx - xs), (cy - xy), time])
                #elif id == 8:
                    #lmlist.append([3, cx, cy, time])
                if draw:
                    cv2.circle(img, (cx, cy), 3, (255, 0, 255), cv2.FILLED)
        return lmlist
    
detector = handDetector()

def main():
    startTime = time.time()
    pTime = 0
    cTime = 0
    cap = cv2.VideoCapture(0)
    
    """EDIT HERE FOR YOUR COM PORT"""
    cereal = serial.Serial(port='COM3', baudrate=115273, timeout=1)
    
    while True:
        success, img = cap.read()
        img = detector.findHands(img)
        detector.lmlist = detector.findPosition(img, cTime)
        if len(detector.lmlist) != 0:
            #print(detector.lmlist)
            str1 = " ".join(map(str, detector.lmlist))
            #str1 = "[2, 185, 289, 15.920351028442383]"
            print(str1)
            cereal.write(bytes(str1, 'utf-8'))

        cTime = time.time() - startTime
        fps = 1 / (cTime - pTime)
        pTime = cTime


        cv2.putText(img, str(int(fps)), (10, 70), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)

        cv2.imshow("Image", img)
        cv2.waitKey(1)




if __name__ == "__main__":

    while True: 
        try:
            main()
        except KeyboardInterrupt:
            print('Interupt Recognized')
            print('please wait while data is saved')
            with open ("data.csv", "w") as file:
                for (a) in zip(detector.lmlist):
                    file.write('{:}\r'.format(a))
            print('data saved!')
            break