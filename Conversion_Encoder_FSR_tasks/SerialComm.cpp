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
#include <fstream>
#include <iostream>


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
 *           coords and time stamp belong to, and then saves them to the appropriate variables
 */
void SerialComm::read(void)
{
    // Serial.println("waiting for char");
    if (Serial.available() > 0)
    {
        String string;
        char term = ']';
        string = Serial.readStringUntil(term);
        string.replace(" ","");
        int index = string.indexOf(',');
        int finger = string.substring(1, index).toInt();
        string = string.substring(index+1);
        
        {
            if (finger == 2)
            {
                index = string.indexOf(',');
                int x1 = string.substring(0, index).toInt();

                string = string.substring(index+1);
                int y1 = string.substring(0, index).toInt();

                string = string.substring(index+1);
                float t1 = string.toFloat();

            }

            else if (finger == 3)
            {
                index = string.indexOf(',');
                int x2 = string.substring(0, index).toInt();

                string = string.substring(index+1);
                int y2 = string.substring(0, index).toInt();

                string = string.substring(index+1);
                float t2 = string.toFloat();

            }
        }
        
    }
}   


/** @brief   Method which returns the x coordinate for motor 1
 *  @details This method returns the most recently updated x-coordinate
 *           for motor 1
 */
int32_t SerialComm::return_x1(void)
{
    return x1;
}

/** @brief   Method which returns the y coordinate for motor 1
 *  @details This method returns the most recently updated y-coordinate
 *           for motor 1
 */
int32_t SerialComm::return_y1(void)
{
    return y1;
}

/** @brief   Method which returns the time stamp for motor 1
 *  @details This method returns the most recently updated time stamp
 *           for motor 1
 */
int32_t SerialComm::return_t1(void)
{
    return t1;
}

/** @brief   Method which returns the x coordinate for motor 2
 *  @details This method returns the most recently updated x-coordinate
 *           for motor 2
 */
int32_t SerialComm::return_x2(void)
{
    return x2;
}

/** @brief   Method which returns the y coordinate for motor 2
 *  @details This method returns the most recently updated y-coordinate
 *           for motor 2
 */
int32_t SerialComm::return_y2(void)
{
    return y2;
}

/** @brief   Method which returns the time stamp for motor 2
 *  @details This method returns the most recently updated time stamp
 *           for motor 2
 */
int32_t SerialComm::return_t2(void)
{
    return t2;
}