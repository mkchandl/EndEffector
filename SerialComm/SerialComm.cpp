/** @file SerialComm.cpp
 *  This file contains the methods for a class the enables serial communication
 *  within the task conversion for the me507 end effector project. 
 * 
 *  @author  Michelle Chandler
 *  @date    2021-Nov-22 Original file
 */

#include <Arduino.h> 
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
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
void SerialComm::read(void)
{
    // Serial.println("waiting for char");
    if (Serial.available() > 0)
    {
        char buf[2];
        int rlen = Serial.readBytes(buf, 1);
        if(rlen > 0)
        {
            if (buf[0] == 'p')
            {
                Serial.println("entered if = P loop"); // for testing
                delay(2000);
                Serial.print("# char available to read:");
                Serial.println(Serial.available());
                x1 = Serial.parseInt();
                Serial.print("just read x1: ");
                Serial.println(x1);
                y1 = Serial.parseInt();
                Serial.print("just read y1: ");
                Serial.println(y1);
                t1 = Serial.parseInt();
                Serial.print("just read t1: ");
                Serial.println(t1);


            }

            else if (buf[0] == 't')
            {
                Serial.println("entered if = t loop"); // for testing
                delay(2000);
                Serial.print("# char available to read:");
                Serial.println(Serial.available());
                x2 = Serial.parseInt();
                Serial.print("just read x2: ");
                Serial.println(x2);
                y2 = Serial.parseInt();
                Serial.print("just read y2: ");
                Serial.println(y2);
                t2 = Serial.parseInt();
                Serial.print("just read t2: ");
                Serial.println(t2);

            }
        }
        
    }
}   

int32_t SerialComm::return_x1(void)
{
    return x1;
}

int32_t SerialComm::return_y1(void)
{
    return y1;
}

int32_t SerialComm::return_t1(void)
{
    return t1;
}

int32_t SerialComm::return_x2(void)
{
    return x2;
}

int32_t SerialComm::return_y2(void)
{
    return y2;
}

int32_t SerialComm::return_t2(void)
{
    return t2;
}