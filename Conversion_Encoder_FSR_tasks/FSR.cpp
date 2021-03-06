/** @file FSR.cpp
 *    This file contains the methods for a class for the FSR, which monitors the contact
 *    between the two fingers and tells the conversion task to shutoff the motors if the
 *    measured contact is too great. 
 * 
 *  @author Michelle Chandler and Cole Andrews
 *  @date  2021-Nov-18 Original file
 */

#include <Arduino.h> 
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "FSR.h"
#include "shares.h"

/** @brief   Create a FSR object
 *  @details This constructor saves the FSR pin 
 *  @param FSR_pin This parameter represents the fsr pin on the nucleo
 */
FSR::FSR(int FSR_pin)
{
    // constructor
    _FSR_pin = FSR_pin;
    motor_shutoff.put(0);
}


/** @brief   Check for contact with the FSR
 *  @details This method checks for any kind of contact with the FSR and
 *           shuts off the motors if the force is too great.
 */
void FSR::checkforcontact(void)
{
    // be constantly checking for contact
    // once contact is detected, bool contact = True
    int fsrReading = analogRead(_FSR_pin); // will read between 0 (no contact) and 1023 (max force)
    if (fsrReading > 1023/2) // 20lbs max so 1023/2 should be 10lbs
    {
        motor_shutoff.put(1);
    }
}


