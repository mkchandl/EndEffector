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
        char buf[2];
        int rlen = Serial.readBytes(buf, 1);
        if(rlen > 0); // originally if(Serial.readBytes(buffer, 1)!=0) but was going into for loop when buffer = {null}
        {
            // Serial.print("read into buffer"); 
            Serial.print("buffer:"); // THis is showing buffer: NULL so its not successfully reading into buffer 
            Serial.println(buf[0]);
            if (buf[0] == 'P')
            {
                Serial.print("entered if = P loop");
                x1 = Serial.parseInt();
            
                y1 = Serial.parseInt();
            
                t1 = Serial.parseInt();
            }

            else if (buf[0] == 'T')
            {
                x2 = Serial.read();
                y2 = Serial.read();
                t2 = Serial.read();
                return x1;
                return y1;
                return t1;
            }
        }
        
    }
}   