/** @file SerialComm.cpp
 *  This file contains the methods for a class the enables serial communication
 *  within the task conversion for the me507 end effector project. 
 * 
 *  @author  Michelle Chandler
 *  @date    2021-Nov-22 Original file
 */

#include <Arduino.h> 
#include <PrintStream.h>
#include "SerialComm.h"

/** @brief   Constructor for the serial comm class
 *  @details This constructor intializes the class object variables
 */
SerialComm::SerialComm(void)
{
    x1 = 0;
    y1 = 0;
    t1 = 0;

    y2 = 0;
    x2 = 0;
    t2 = 0;
}



/** @brief   Method which reads from serial port
 *  @details This method reads from the serial port, determines which finger the 
 *           coords and time stamp belong to, and then save them to the appropriate 
 *           array
 *  @return  a 1x4 array with finger indentification, x and y coord, and time stamp
 */
int32_t SerialComm::read(void)
{
    if (Serial.available() > 0)
    {
        char buffer[2];
        char finger = Serial.readBytes(buffer, 1);
        if (finger == 'P')
        {
            Serial.print("entered if finger = P loop");
            x1 = Serial.parseInt();
            
            y1 = Serial.parseInt();
            
            t1 = Serial.parseInt();

            Serial.print("x1:");
            Serial.println(x1);
            Serial.print("y1:");
            Serial.println(y1);
            Serial.print("t1:");
            Serial.println(t1);
        }
        else if (finger == 'T')
        {
            x2 = Serial.read();
            y2 = Serial.read();
            t2 = Serial.read();
        }
    }
}
