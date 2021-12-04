/** @file MotorDriver.cpp
 *  This file contains a motor driver for a simple brushed DC motor
 *  This driver was based off of my ME 405 motor driver in python and the 
 *  arduino documentation.
 * 
 *  @author  Michelle Chandler
 *  @date    2021-Oct-28 Original file
 */

#include <Arduino.h> 
#include <PrintStream.h>
#include "MotorDriver.h"

/** @brief   Motor driver class for a brushed DC motor
 *  @details This class drives motors using the arduino library and allows 
 *           for complete control of the motor using PWM. 
 *  @param   sleep This parameter represents the sleep pin on the motor driver breakout board. 
 *  @param   IN1A This parameter represents one of two motor wires?pins? that control the duty cycle and direction
 *  @param   IN1A This parameter represents one of two motor wires?pins? that control the duty cycle and direction
 *  @param   nFault This parameter represents the nFault pin on the motor driver board
 */
MotorDriver::MotorDriver(uint8_t sleep, uint8_t IN1A, uint8_t IN2A, uint8_t nFault)
{
    _sleep = sleep; // saving param given to constructor as var for class
    _IN1A = IN1A;
    _IN1B = IN2A;
    _nFault = nFault;

    pinMode(sleep, OUTPUT);
    pinMode(nFault, OUTPUT);
    pinMode(IN1A, OUTPUT);
    pinMode(IN2A, OUTPUT);

   digitalWrite(_sleep, LOW);
   digitalWrite(_nFault, LOW);
}


/** @brief   This function enables the motors
 *  @details This function enables motor dring by setting the sleep pin high
 */
void MotorDriver:: enable(void)
{
    digitalWrite(_sleep, HIGH);
}


/** @brief   This function disables the motors
 *  @details This function disables the motors by setting the sleep pin low
 */
void MotorDriver:: disable(void)
{
    digitalWrite(_sleep, LOW);
}


/** @brief   This function sets the duty cycle of the motor
 *  @details This function uses PWM to control the speed of the motor
 *  @param duty2 This parameter represents the requeested duty cycle to be handed to the motor
 */
void MotorDriver:: set_duty2(int16_t duty2)
{
    /// Set duty limits to -100% and 100%
    if (duty2>100)
    {
        duty2 = 100;
    }
    else if (duty2 < -100) 
    {
        duty2 = -100;
    }

    ///Set duty by translating duty cycle into a 16-bit value
    if (duty2 >= 0)
    {
        int16_t value2 = (int16_t)(duty2*(2.55/2));
        digitalWrite(_IN1A, LOW);
        analogWrite(_IN1B, value2);
    }
    else if (duty2 < 0)
    {
        int16_t value2 = (int16_t)(-1*duty2*2.55);
        digitalWrite(_IN1B, LOW);
        analogWrite(_IN1A, value2);
    }
}