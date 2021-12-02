/** @file MotorDriver.cpp
 *  This file contains a motor driver for a simple brushed DC motor
 *  This driver was based off of my ME 405 motor driver in python
 * 
 *  @author  Michelle Chandler
 *  @date    2021-Oct-28 Original file
 */

#include <Arduino.h> 
#include <PrintStream.h>
#include "MotorDriver.h"

/** @brief   Create a Motor Driver
 *  @details This constructor 
 *  @param 
 */
MotorDriver::MotorDriver(uint8_t sleep, uint8_t IN1A, uint8_t IN2A, uint8_t nFault)
{
    _sleep = sleep; // saving param given to constructor as var for class
    _IN1A = IN1A;
    _IN1B = IN2A;
    _nFault = nFault;

    // QUESTIONS set up nsleep and nfault as outputs?
    pinMode(sleep, OUTPUT);
    pinMode(nFault, OUTPUT);
    /* for other pins will want to be able to change the direction of motor
        so instead of setting one as the output here, set them in the set 
        duty method
        OR
        QUESTIONdo i set both pins as outputs and digitalWrite(IN1/2A/B HIGH/LOW)?
    */
   pinMode(IN1A, OUTPUT);
   pinMode(IN2A, OUTPUT);

    // setting low for safety?
   digitalWrite(_sleep, LOW);
   digitalWrite(_sleep, LOW);
}


/** @brief   
 *  @details This function
 */
void MotorDriver:: enable(void)
{
    digitalWrite(_sleep, HIGH);
}


/** @brief   
 *  @details This function 
 */
void MotorDriver:: disable(void)
{
    digitalWrite(_sleep, LOW);
}


/** @brief   
 *  @details This function 
 */
void MotorDriver:: set_duty2(uint16_t duty2)
{
    // limit duty
    if (duty2>100)
    {
        duty2 = 100;
    }
    else if (duty2 < -100) 
    {
        duty2 = -100;
    }

    // set duty
    if (duty2 >= 0)
    {
        //Serial << "Duty2: " << endl;
        Serial.println(duty2);
        uint16_t value2 = (uint16_t)(duty2*2.55);
        //Serial << "Value: " << endl;
        Serial.println(value2);
        digitalWrite(_IN1A, LOW);
        analogWrite(_IN1B, value2);
    }
    else if (duty2 < 0)
    {
        //Serial << endl << endl << "Duty2: " << endl;
        Serial.println(duty2);
        uint16_t value2 = (uint16_t)(-1*duty2*2.55);
        //Serial << endl << endl << "Value: " << endl;
        Serial.println(value2);
        digitalWrite(_IN1B, LOW);
        analogWrite(_IN1A, value2);
    }
}