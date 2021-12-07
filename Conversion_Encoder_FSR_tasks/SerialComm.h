/** @file SerialComm.h
 *  This file contains the headers for a class the enables serial communication
 *  within the task conversion for the me507 end effector project. 
 * 
 *  @author  Michelle Chandler and Cole ANdrews
 *  @date    2021-Oct-28 Original file
 */

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h> 
#endif


class SerialComm
{
    protected: 
        int32_t x1;
        int32_t y1;
        int32_t t1;

        int32_t x2;
        int32_t y2;
        int32_t t2;

    public: 
        SerialComm(void); // constructor. may need params passed in
        void read(void); // method that reads from serial port. 
        void write(void); // writes to the serial port
        int32_t return_x1(void);
        int32_t return_y1(void);
        int32_t return_t1(void);
        int32_t return_x2(void);
        int32_t return_y2(void);
        int32_t return_t2(void);
};