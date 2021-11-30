# -*- coding: utf-8 -*-
"""
Created on Mon Nov 29 15:12:09 2021

@author: CCHAN
"""

import serial 

ser = serial.Serial(port= 'COM5', baudrate=115273, timeout=3)

x1 = []
y1 = []
t1 = []

ref = open('data.csv');
while True:
    # Read a line of data. It should be in the format 't,v,x\n' but when the
    # file runs out of lines the lines will return as empty strings, i.e. ''
    line = ref.readline()
    # If the line is empty, there are no more rows so exit the loop
    if line == '':
        break
    # If the line is not empty, strip special characters, split on commas, and
    # then append each value to its list.
    else:
        print('making x coord, y coord, time stamp arrays')
        (x, y, t) = line.strip().split(',');
        # add values from the csv file to respective time, position, velocity arrays
        x1.append(float(x))
        y1.append(float(y))
        t1.append(float(t))
# Can't forget to close the serial port
ref.close()
print('closed data.csv')

lmlist= []
lmlistx1= []
lmlisty1= []
lmlistt1= []

n=0
while n < len(x1):
    lmlist.append("t", x1[n], y1[n], t1[n])
    str1 = "".join(map(str, lmlist))
    ser.write(bytes(str1, 'utf-8'))
    print(str1)
    n+=1
    
# while n < len(x1):
#     lmlistx1.append(x1[n])
#     strx1 = " ".join(map(str, lmlistx1))
#     lmlisty1.append(y1[n])
#     stry1 = " ".join(map(str, lmlisty1))
#     lmlisty1.append(t1[n])
#     strt1 = " ".join(map(str, lmlistt1))
#     #ser.write(bytes(strx1, 'utf-8'))
#     print(strx1)
#     n+=1    

ser.close()