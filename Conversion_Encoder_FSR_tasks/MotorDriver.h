/** @file MotorDriver.cpp
 *  This file contains a motor driver for a simple brushed DC motor
 *  This driver was based off of my ME 405 motor driver in python
 * 
 *  @author  Michelle Chandler and Cole Andrews
 *  @date    2021-Oct-28 Original file
 */

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h> 
#endif

class MotorDriver
{
protected:
    // values only accessed by objects of that class
    // will want to put pins here IN1A etc bc only in  constructor rn so will only exist there
    // make variables w same names but w underscore in front
    uint8_t _sleep;
    uint8_t _IN1A;
    uint8_t _IN1B;
    uint8_t _nFault;



public:
    //constructor
    MotorDriver(uint8_t sleep, uint8_t IN1A, uint8_t IN2A, uint8_t nFault);

    void enable(void); // sets sleep pin high
    void disable(void); // will set sleep pin low
    void set_duty2(int16_t duty1); // will set duty of motor. duty between 0 and 255
};